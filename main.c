#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "io.h"
#include "btree.h"
//#include "funciones.h"
#define ARCHIVO "prueba.txt"


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

void contar_caracteres(BTree* duplas, char* buf, size_t len){
  for (int i = 0; i < len; i++) {
    duplas[(unsigned char)buf[i]]->peso++;
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

void ordena_duplas(BTree* duplas, int inicio){ /* Inserción */
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

BTree armar_arbol(BTree* duplas){ 
  int i = 0;
  for (; i < 255; i++){
    if (duplas[i]->peso > duplas[i+1]->peso){
      ordena_duplas(duplas, i);
    }
    duplas[i+1] = btree_unir(duplas[i], duplas[i+1]);
  }
  return duplas[i];
}

/* Función copiada de P4E3, es para recorrer el arbol y mostrarlo */
static void imprimir_caracter(char data) {
  printf(": '%c'\n", data);
}

int main(){
  BTree* duplas;
  char test[] = "hol aisndiofn oqwapmdosada jpoij¿roirew0 i4'¿523¿'423++* ";
  duplas = crear_duplas();
  contar_caracteres(duplas, test, strlen(test));

  //mostrar_duplas(duplas);
  ordena_duplas(duplas, 0);
  //puts("Duplas ordenadas");
  //mostrar_duplas(duplas);
  
  BTree arbol = malloc(sizeof(Nodo));
  arbol = armar_arbol(duplas);
  btree_recorrer(arbol, BTREE_RECORRIDO_PRE, imprimir_caracter);
  puts("\n");


  return 0;
}
