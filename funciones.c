#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

BTree crear_duplas(){
  BTree nodos[256];
  for (int i = 0; i < 256; i++){
    BTree nuevo = malloc(sizeof(struct _BTNodo));
    nuevo->caracter = i;
    nuevo->peso = 0;
    nuevo->left = nuevo->right = btree_crear();
    nodos[i] = nuevo;
    printf("caracter agregado: %c\n", nodos[i]->caracter);
  }
  return nodos;
}


void contar_caracteres(BTree *duplas, char* buf, int len){
  for (int i = 0; i < len; i++){
    duplas[buf[i]]->peso++;
  }
}




