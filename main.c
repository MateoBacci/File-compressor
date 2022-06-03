#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "io.h"
#include "btree.h"
#include "funciones.h"

int main(int argI, char *argC[3]){

  if (argC[1][0] == 'C' || argC[1][0] == 'c') {

    char *fileName = argC[2];
    int bufLen;
    char *buf = readfile(fileName, &bufLen);
    BTree* duplas = crear_duplas();
    contar_caracteres(duplas, buf, bufLen);
    ordena_duplas(duplas, 0);

    BTree arbol = btree_armar(duplas);
    free(duplas);
    
    
    char *codeArbol = malloc(sizeof(char) * CANT_CHARS * 3);
    char *codeChars[CANT_CHARS];
    char *aux = malloc(CANT_CHARS * sizeof(char));
    char *pathTree = malloc(sizeof(char) * strlen(fileName) + 6);
    int lenCode = 0, lenChars = 0;
    strcpy(pathTree, fileName);
    strcat(pathTree, ".tree");

    btree_codificacion(arbol, codeArbol, &lenCode, &lenChars);
    writefile(pathTree, codeArbol, (CANT_CHARS*3) - 1);
    free(pathTree);
    
    char_codificacion(arbol, aux, codeChars, 0);
    btree_destruir(arbol);
    free(codeArbol);
    free(aux);


    int nLen;
    char* pathHf = malloc(sizeof(char) * strlen(fileName) + 4);
    strcpy(pathHf, fileName);
    strcat(pathHf, ".hf");
    char *bufCodificado = codificar_texto(buf, bufLen, codeChars, &nLen);
    free(buf);
    destruir_arreglo(codeChars);  

    char *bufImplotado = implode(bufCodificado, strlen(bufCodificado), &nLen);
    free(bufCodificado);

    writefile(pathHf, bufImplotado, nLen);
    free(bufImplotado);
    free(pathHf);

    printf("Listo!\n");
    return 0;
  }
  else if (argC[1][0] == 'D' || argC[1][0] == 'd') {
    char *fileName = argC[2];
    int bufLen, bufELen;
    char *buf = readfile(fileName, &bufLen);
    char *bufExploded = explode(buf, bufLen, &bufELen);
    free(buf);

    char *pathTree = cambio_archivo(fileName, "tree");

    int codeArbolLen, contA = 0, contB = 0;
    char *codeArbol = readfile(pathTree, &codeArbolLen);;
    BTree arbol = arbol_desde_texto(codeArbol, &contA, &contB);
    free(pathTree);
    free(codeArbol);

    int lenDecoded = 0;
    char *textoDecodificado;
    textoDecodificado = decodificar_texto(arbol, bufExploded, bufELen, &lenDecoded);
    free(bufExploded);
    btree_destruir(arbol);
    
    char *pathDec = cambio_archivo(fileName, "dec");
    writefile(pathDec, textoDecodificado, lenDecoded);
    free(pathDec);
    free(textoDecodificado);
    puts("Listo!");
    return 1;
  }

  perror("Caracter no aceptado, elija 'C' o 'D'");
  return 2;
}
