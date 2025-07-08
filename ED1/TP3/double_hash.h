//arquivo de cabecalho(header) com os prototipos das funcoes e estruturas

#ifndef DOUBLE_HASH_H
#define DOUBLE_HASH_H
#include "automato.h"

//funcao de hash1
int hash1(int x, int y, int tamanho);

//funcao de hash2
int hash2(int x, int y, int tamanho);

//funcao para inserir na hash
void inserirHash(Reticulado* reticulado, int i, int j, int valor);

//funcao para pesquisar determinado elemento na hash
int pesquisarCelula(Reticulado* reticulado, int x, int y);

#endif