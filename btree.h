#ifndef __BTREE_H__
#define __BTREE_H__

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

typedef struct _BTNodo *BTree;

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
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(BTree left, BTree right);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit);


int btree_nnodos(BTree arbol);

int btree_buscar(BTree arbol, char carcater);

BTree btree_copiar(BTree arbol);

int btree_altura(BTree arbol);

int btree_profundidad(BTree arbol, char dato);

int btree_sumar_peso(BTree arbol);


#endif /* __BTREE_H__ */
