#include "btree.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() { return NULL; }

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo) { return nodo == NULL; }

/**
 * 
 */
BTree btree_unir(BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(Nodo));
 
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  nuevoNodo->peso = left->peso + right->peso; 
  return nuevoNodo;
}

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, 
                    BTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit) {
  
  if (btree_empty(arbol)) return;

  
  if (orden == BTREE_RECORRIDO_PRE){
    if (btree_empty(arbol->left) && arbol->peso)
      visit(arbol->caracter);
  }
  printf("0");
  btree_recorrer(arbol->left, orden, visit);

  if (orden == BTREE_RECORRIDO_IN){
    if (btree_empty(arbol->left) && arbol->peso)
      visit(arbol->caracter);
  }
  printf("1");
  btree_recorrer(arbol->right, orden, visit);

  if (orden == BTREE_RECORRIDO_POST){
    if (btree_empty(arbol->left) && arbol->peso)
      visit(arbol->caracter);
  }
  puts("");
  return;
}

/*
int btree_codificacion(BTree arbol, char* codificacion) {

  int i=0;

  if (btree_empty(arbol)) return i;
  
  int caracterAgregado = 0;
  
  if (btree_empty(arbol->left) && arbol->peso){
    printf("'%c'\n", arbol->caracter);
    caracterAgregado = 1;
  }

  
  if (!caracterAgregado && arbol->peso) {
    printf("0 ");
    codificacion = realloc(codificacion, i+2);
    codificacion[i] = '0';
  }

  i += btree_codificacion(arbol->left, codificacion);

  if (!caracterAgregado && arbol->peso) {
    printf("1 ");
    codificacion = realloc(codificacion, i+1);
    codificacion[i] = '1';
  }
  i += btree_codificacion(arbol->right, codificacion);

  return i;
}

*/


int btree_nnodos(BTree arbol){
  if (btree_empty(arbol))
    return 0;

  return 1 + btree_nnodos(arbol->left) + btree_nnodos(arbol->right);
}


int btree_buscar(BTree arbol, char caracter){

  if (btree_empty(arbol))
    return 0;

  return arbol->caracter == caracter
      || btree_buscar(arbol->left, caracter)
      || btree_buscar(arbol->right, caracter);
}


BTree btree_copiar(BTree arbol){
  BTree nuevoArbol = malloc(sizeof(Nodo));
  nuevoArbol->caracter = arbol->caracter;
  nuevoArbol->left = arbol->left;
  nuevoArbol->right = nuevoArbol->right;
  nuevoArbol->peso = arbol->peso;
  return nuevoArbol;
}


int btree_altura(BTree arbol){
  if (btree_empty(arbol))
    return -1;

  int lh, rh;

  lh = btree_altura(arbol->left);
  rh = btree_altura(arbol->right);

  if (lh > rh)
    return 1+lh;
  else
    return 1+rh;
}


int btree_profundidad(BTree arbol, char dato){
  if (btree_empty(arbol))
    return -1;

  printf("Dato actual: %c\n", arbol->caracter);
  if (arbol->caracter == dato)
    return 0;

  int t = btree_profundidad(arbol->left, dato);
  if (t >= 0)
    return 1+t;

  t = btree_profundidad(arbol->right, dato);
  if (t >= 0)
    return 1+t;

  return -1;
}


int btree_sumar_peso(BTree arbol){
  if (btree_empty(arbol))
    return 0;

  return arbol->peso + btree_sumar_peso(arbol->left) + btree_sumar_peso(arbol->right);
}


