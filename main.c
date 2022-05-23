#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "io.h"
#include "btree.h"
//#include "funciones.h"
#define ARCHIVO "prueba.txt"



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
  for (int i = 0; i < len; i++) {
    int posicion = (unsigned)buf[i];
    duplas[posicion]->peso++;
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
  printf("%d", duplas[i]->peso);
  return *duplas;
}



int main(){
  BTree* duplas;
  char test[] = "hol aisndiofn oqwapmdosada jpoij¿roirew0 i4'¿523¿'423++* ";
  duplas = crear_duplas();
  contar_caracteres(duplas, test, strlen(test));
  ordena_duplas(duplas, 0);
  mostrar_duplas(duplas);

  BTree arbol = malloc(sizeof(Nodo));
  arbol = armar_arbol(duplas);
  
  puts("Hola");
  return 0;
}
