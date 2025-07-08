#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "registro.h"

typedef struct {
    Registro item;
    long esq;  // filho esquerdo
    long dir;  // filho direito
} tipoNo;

bool ArvoreBinaria(FILE *arq, int quantidade, int chave, bool print, Registro *item, int *transferencias, int *comparacoes);
void insereNaArvore(FILE *arqAbp, Registro itemInserir, int *transferencias, int *comparacoes);
void constroiArvore(FILE *arq, FILE *arqAbp, int quantidade, int *transferencias, int *comparacoes);
bool pesquisarAbp(FILE *arqAbp, int chave, Registro *item, int *transferencias, int *comparacoes);
void imprimeAbp(FILE *arqAbp, long ponteiro);


#endif
