#ifndef __BTREE_H__
#define __BTREE_H__

#ifndef CANT_CHARS
#define CANT_CHARS 256
#endif


typedef void (*FuncionVisitante)(char dato);

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

typedef struct _BTNodo {
  int peso;
  char caracter;
  struct _BTNodo *left;
  struct _BTNodo *right;
} Nodo;

typedef Nodo* BTree;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo);

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo);

/**
 * Crea un nuevo arbol cuyo peso es la suma de los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(BTree left, BTree right);


int es_hoja(BTree arbol);


/**
 * Recorre el arbol y guarda en un arreglo su codificación y los caracteres en 
 * orden.
 * codificacion[0 - 510] -> codificacion del arbol
 * codificacion[511 - 767] -> caracteres en el orden en que aparecen en el arbol
 */
void btree_codificacion(BTree arbol, char* code, int* contTotal, int* contUnos);

BTree btree_armar(BTree* duplas);

#endif /* __BTREE_H__ */
