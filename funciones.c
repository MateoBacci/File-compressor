#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "btree.h"

BTree* crear_duplas(){
  BTree* nodos = malloc(sizeof(BTree) * CANT_CHARS);
  for (int i = 0; i < CANT_CHARS; i++) {
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

void mostrar_duplas(BTree* duplas){
  for (int i = 0; i < CANT_CHARS; i++) {
    if (duplas[i]->peso)
      printf("char: '%c', peso: %d\n", duplas[i]->caracter, duplas[i]->peso);
  }
}

void ordena_duplas(BTree* duplas, int inicio){ /* Selección */
  int min, minPos;
  BTree aux;
  for (int i = inicio; i < CANT_CHARS; i++) {
    minPos = i;
    for (int j = i+1; j < CANT_CHARS; j++) {
      if (duplas[j]->peso < duplas[minPos]->peso)
        minPos = j;
    }
    aux = duplas[i];
    duplas[i] = duplas[minPos];
    duplas[minPos] = aux;
  }
}

void duplas_destruir(BTree* duplas){
  btree_destruir(*duplas);
  free(duplas);
}

/**
 * chars[i] = codificacion en el arbol del caracter en la posicion i de la 
 * tabla ascii
 *
 * - Ej: 
 *     Codificacion de 'A' en el arbol: 00011
 *     'A' en tabla ASCII: 65
 *     chars[65] = "00011"
*/
void char_codificacion (BTree arbol, char* strAux, char* arreglo[CANT_CHARS], int contador){
  if (btree_empty(arbol)){
    contador--; 
    return;
  }
  if (es_hoja(arbol)) {
    int pos = (unsigned char)arbol->caracter;
    printf("%d %s\n", contador, strAux);
    arreglo[pos] = malloc(contador + 1);
    strncpy(arreglo[pos], strAux, contador);
  } else {
    strAux[contador] = '0';
    contador++;
  }
  char_codificacion(arbol->left, strAux, arreglo, contador);
  strAux[contador-1] = '1';
  char_codificacion(arbol->right, strAux, arreglo, contador);
}

char* codificar_texto(char* buf, int len, char* codes[CANT_CHARS], int* nLen){
  char* textoCodificado = malloc(1);
  int textLen = 0;
  for (int i = 0; i < len; i++) {
    int pos = (unsigned char)buf[i];
    textLen += strlen(codes[pos]);
    textoCodificado = realloc(textoCodificado, textLen + 1);
    textoCodificado = strcat(textoCodificado, codes[pos]);
  }
  *nLen = textLen;
  return textoCodificado;
}
