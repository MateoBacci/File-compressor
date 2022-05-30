#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "io.h"
#include "btree.h"
//#include "funciones.h"





/* Crea e inicializa 256 hojas (árboles con peso 0 y sin hijos), asignandole
 * un caracter de la table ASCII a cada uno.
 */
BTree* crear_duplas(){
  BTree* nodos = malloc(sizeof(BTree) * 256);
  for (int i = 0; i < 256; i++) {
    BTree nuevo = malloc(sizeof(Nodo));
    nuevo->caracter = i;
    nuevo->peso = 0;
    nuevo->left = nuevo->right = btree_crear();
    nodos[i] = nuevo;
  }
  return nodos;
}

void contar_caracteres(BTree* duplas, char* buf, int len){
  int pos, cont = 0;
  for (int i = 0; i < len; i++) {
    pos = (unsigned char)buf[i];
    duplas[pos]->peso++;
  }
}

void mostrar_peso(BTree* duplas){
  for (int i=0; i < 256; i++) {
    if (duplas[i]->peso != 0){
      printf("%c - %d\n", duplas[i]->caracter, duplas[i]->peso);
    }
  }
}

void mostrar_duplas(BTree* duplas){
  for (int i = 0; i < 256; i++) {
    if (duplas[i]->peso)
      printf("char: '%c', peso: %d\n", duplas[i]->caracter, duplas[i]->peso);
  }
}

void ordena_duplas(BTree* duplas, int inicio){ /* Selección */
  int min, minPos;
  BTree aux;
  for (int i = inicio; i < 255; i++) {
    minPos = i;
    for (int j = i+1; j < 256; j++) {
      if (duplas[j]->peso < duplas[minPos]->peso)
        minPos = j;
    }
    aux = duplas[i];
    duplas[i] = duplas[minPos];
    duplas[minPos] = aux;
  }
}


BTree btree_armar(BTree* duplas){ 
  int i = 0;
  for (; i < 255; i++){
    if (duplas[i]->peso > duplas[i+1]->peso)
      ordena_duplas(duplas, i);
    duplas[i+1] = btree_unir(duplas[i], duplas[i+1]);
  }
  return duplas[i];
}

void duplas_destruir(BTree* duplas){
  btree_destruir(*duplas);
  free(duplas);
}

/*
* chars[i] = codificacion en el arbol del caracter en la posicion i de la 
* tabla ascii
*
* - Ej: 
*     Codificacion de 'A' en el arbol: 00011
*     chars[65] = "00011"
*/



void char_codificacion (BTree arbol, char* strAux, char* arreglo[256], int contador){
  
  printf("%s %d\n", strAux, contador);
  if (btree_empty(arbol)){
    contador--; 
    return;
  }

  if (btree_empty(arbol->left)) {
    int pos = (unsigned char)arbol->caracter;
    arreglo[pos] = malloc(contador);
    arreglo[pos] = strAux;
  } else {
    strAux[contador] = '0';
    contador++;
  }

  char_codificacion(arbol->left, strAux, arreglo, contador);

  strAux[contador-1] = '1';
  char_codificacion(arbol->right, strAux, arreglo, contador);

} 



/*
void char_codificacion(char* codeTree, char* newCodesChar[256]){
  char* strAux = malloc(1);
  int j = 0; // j = 0, ..., 255
  int len = 0;
  for (int i = 0; i < 511; i++){
    if (codeTree[i] == '0'){
      len++;
      strAux = realloc(strAux, len);
      strAux[i] = '0';
    }
    else {
      int pos = (unsigned char)codeTree[j+511];
      newCodesChar[pos] = malloc(len);
      newCodesChar[pos] = strAux;
      if (strAux[len-1]) {
        len--;
        strAux = realloc(strAux, len);
      } 
      strAux[len-1] = '1';
      j++;
    }
    printf("%s - %d\n", strAux, len);
  }
}
*/


/* Función copiada de P4E3, es para recorrer el arbol y mostrarlo */
static void imprimir_caracter(char data) {
  printf(": '%c'\n", data);
}

int main(){
  BTree* duplas;
  char *buf;
  int bufLen;

  /* Armamos el arreglo de arboles ("duplas"), que serán las hojas en el arbol
   * final. "Armar" el arreglo consiste en reservar el espacio en memoria de 256
   * arboles (BTree), inicializar el peso de todos a 0 y sus hijos a NULL, luego
   * recorrer el buf y contar cuántas veces aparece cada caracter. Finalmente, 
   * ordenar de menor a mayor las 256 hojas según su peso.   
   */

  buf = readfile("prueba.txt", &bufLen);
  duplas = crear_duplas();
  contar_caracteres(duplas, buf, bufLen);
  ordena_duplas(duplas, 0);

  BTree arbol;
  arbol = btree_armar(duplas);
  char *codeArbol = malloc(768);
  char *caracteres[256];
  char *aux = malloc(256 / 2);
  int cont = 0;
  //btree_codificacion(arbol, codeArbol, 0);

  char_codificacion(arbol, aux, caracteres, cont);
  duplas_destruir(duplas);
  return 0;
}
