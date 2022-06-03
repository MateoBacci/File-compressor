#include "btree.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
};

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
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit) {
  if (btree_empty(arbol)) return;

  if (orden == BTREE_RECORRIDO_PRE)
    visit(arbol->dato);       /* Si es preorder: se muestra primero la raiz */

  btree_recorrer(arbol->left, orden, visit);

  if (orden == BTREE_RECORRIDO_IN)
    visit(arbol->dato);     /* Si es inorder: la raiz se muestra segunda */

  btree_recorrer(arbol->right, orden, visit);

  if (orden == BTREE_RECORRIDO_POST)
    visit(arbol->dato);     /* Si es postorder: orden = 2, se muestra la raiz */

  return;
}

/* Ejercicio: */

int btree_nnodos(BTree arbol){
  int cantidad = 0;
  if (btree_empty(arbol))
    return cantidad;

  cantidad ++;

  cantidad += btree_nnodos(arbol->left);

  cantidad += btree_nnodos(arbol->right);
  printf("%d %d\n", arbol->dato, cantidad);
  return cantidad;
}


int btree_nnodos2(BTree arbol){
  if (btree_empty(arbol))
    return 0;

  return 1 + btree_nnodos2(arbol->left) + btree_nnodos2(arbol->right);
}


int btree_buscar(BTree arbol, int dato){

  if (btree_empty(arbol))
    return 0;

  return arbol->dato == dato
      || btree_buscar(arbol->left, dato)
      || btree_buscar(arbol->right, dato);
}


BTree btree_copiar(BTree arbol){
  if (btree_empty(arbol))
    return NULL;

  BTree copia = malloc(sizeof(BTree));

  copia->dato = arbol->dato;

  copia->left = btree_copiar(arbol->left);

  copia->right = btree_copiar(arbol->right);

  return copia;
}

BTree btree_copiar2(BTree arbol){
  if (btree_empty(arbol))
    return NULL;

  return btree_unir(arbol->dato,
                    btree_copiar2(arbol->left),
                    btree_copiar2(arbol->right));
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



int btree_nnodos_profundidad(BTree arbol, int profundidad){
  if (btree_empty(arbol))
    return 0;

}



int btree_profundidad(BTree arbol, int dato){
  if (btree_empty(arbol))
    return -1;

  printf("Dato actual: %d\n", arbol->dato);
  if (arbol->dato == dato)
    return 0;

  int t = btree_profundidad(arbol->left, dato);
  if (t >= 0)
    return 1+t;

  t = btree_profundidad(arbol->right, dato);
  if (t >= 0)
    return 1+t;

  return -1;
}

