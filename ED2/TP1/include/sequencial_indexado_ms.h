#ifndef SEQUENCIAL_INDEXADO_MS_H
#define SEQUENCIAL_INDEXADO_MS_H

#include <stdio.h>
#include "registro.h"  // inclui REG_POR_PAGINA

typedef struct {
    int  chave;       // chave do primeiro registro da pagina
    long posicao;     // posicao no arquivo
} IndicePagina;

// cria indice para arquivo ordenado (memoria secundaria)
IndicePagina* criar_indice_ms(FILE* arq, int total_reg, int* total_paginas, int* transf, int* comp);

// pesquisa um registro no arquivo usando acesso sequencial indexado (memoria secundaria)
Registro* pesquisar_indexado_ms(FILE* arq, IndicePagina* indice, int total_pag, int chave, int* transf, int* comp);

// libera o indice
void liberar_indice_ms(IndicePagina* indice);

// verifica se o arquivo esta ordenado crescentemente pelas chaves
int arquivo_ordenado_ms(FILE* arq);

#endif
