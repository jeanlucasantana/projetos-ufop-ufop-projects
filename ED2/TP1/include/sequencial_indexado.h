#ifndef SEQUENCIAL_INDEXADO_H
#define SEQUENCIAL_INDEXADO_H

#include <stdio.h>
#include "registro.h"  // REG_POR_PAGINA vem daqui

typedef struct {
    int chave;      // chave do primeiro registro na pagina
    long posicao;   // posicao da pagina no vetor
} IndicePagina;

// cria indice em memoria principal (vetor de registros ordenados)
IndicePagina* criar_indice_mp(Registro* vet, int total_reg, int* total_paginas, int* transf, int* comp);

// pesquisa no vetor ordenado usando acesso sequencial indexado em memoria principal
Registro* pesquisar_indexado_mp(Registro* vet, int total_reg, IndicePagina* indice, int total_pag, int chave, int* transf, int* comp);

// libera o indice
void liberar_indice_mp(IndicePagina* indice);

#endif
