#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "io.h"
#include "btree.h"
#include "funciones.h"

void mostrar_chars(char *chars[CANT_CHARS]){
  for (int i = 0; i < CANT_CHARS; i++)
    printf("%d) %s\n", i, chars[i]);
}

int main(int argI, char *argC[3]){

  if (argC[1][0] == 'C' || argC[1][0] == 'c') {

    BTree* duplas;
    char *buf, *fileName = argC[2];
    int bufLen;

    buf = readfile(fileName, &bufLen);
    duplas = crear_duplas();
    contar_caracteres(duplas, buf, bufLen);
    ordena_duplas(duplas, 0);



    BTree arbol = btree_armar(duplas);
    char *codeArbol = malloc(CANT_CHARS*3);
    char *codeChars[CANT_CHARS];
    char *aux = malloc(CANT_CHARS);
    char *pathTree = strcat(fileName, ".tree");;
    int lenCode = 0, lenChars = 0;

    btree_codificacion(arbol, codeArbol, &lenCode, &lenChars);
    writefile(pathTree, codeArbol, (CANT_CHARS*3) - 1);
    char_codificacion(arbol, aux, codeChars, 0);
    mostrar_chars(codeChars);



    char* bufCodificado;
    int nLen;
    char* pathHf = strcat(fileName, ".hf");
  
    bufCodificado = codificar_texto(buf, bufLen, codeChars, &nLen);
    bufCodificado = implode(bufCodificado, strlen(bufCodificado), &nLen);
    writefile(pathHf, bufCodificado, nLen);

    
    /* Liberamos la memoria dinámica */
    duplas_destruir(duplas);
    free(buf);
    for (int i = 0; i < CANT_CHARS; i++)
      free(codeChars[i]);
    free(codeArbol);
    free(aux);


    return 0;
  }
  else if (argC[1][0] == 'D' || argC[1][0] == 'd') {
    char *fileName = argC[2];
    char *buf;
    int bufLen;
    int bufELen;
    buf = readfile(fileName, &bufLen);
    




    char *pathDec = strcat(fileName, ".dec");
    //writefile(pathDec, , )
    return 1;
  }
  perror("Caracter no aceptado, elija 'C' o 'D'");
  return 2;
}
