#include "btree.h"

#ifndef __FUNCIONES_H_
#define __FUNCIONES_H_

/**
 * Crea e inicializa 256 hojas (árboles con peso 0 y sin hijos), asignandole
 * un caracter de la tabla ASCII a cada uno.
 */
BTree* crear_duplas();

/**
*  Recorriendo el buf, va guardando en duplas cuantas veces aparece en el buf
*  cada uno de sus caracteres.
*/
void contar_caracteres(BTree* duplas, char* buf, int len);

/**
*   
*/
void mostrar_duplas(BTree* duplas);

/**
* Función de ordenamiento. Utiliza el algoritmo de ordenamiento por selección
*/
void ordena_duplas(BTree* duplas, int inicio);

void char_codificacion (BTree arbol, char* strAux, char* arreglo[CANT_CHARS], int contador);

char* codificar_texto(char* buf, int len, char* codes[CANT_CHARS], int* nLen);

BTree arbol_desde_texto (char *code, int *pos, int *charsAgregados);

char buscar_caracter(BTree arbol, char* buf, int *pos);

char *decodificar_texto(BTree arbol, char *buf, int len, int *lenDecoded);

char *cambio_archivo (char *fileName, char *dato);

void destruir_arreglo(char *chars[CANT_CHARS]);

#endif /*  __FUNCIONES_H_ */
