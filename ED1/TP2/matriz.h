//arquivo de especificacao da matriz e suas respectivas funcoes
#ifndef MATRIZ_H
#define MATRIZ_H
#include <stdbool.h>

//estrutura para representar uma celula da matriz

typedef struct{
    int linha; //coordenada que representa a linha em que a celula esta posicionada 
    int coluna; //coordenada que representa a coluna em que a celula esta posicionada
} Celula;

//estrutura pra representar uma "celula" da lista encadeada

typedef struct nCelula{
    Celula celula;
    struct nCelula* proximaLinha; //ponteiro para a proxima celula da mesma linha
    struct nCelula* proximaColuna; //ponteiro para a proxima celula da mesma coluna
} nCelula;

//estrutura pra representar a lista de linhas

typedef struct {
    nCelula* primeiraLinha;
} listaLinhas;

//estrutura pra representar a lista de colunas

typedef struct{
    nCelula* primeiraColuna;
} listaColunas;

//funcoes para manipulacao do reticulado

void alocarReticulado(listaLinhas* linhas, listaColunas* colunas);
void desalocarReticulado(listaLinhas* linhas);
void leituraReticulado(listaLinhas* linhas, listaColunas* colunas, int* geracoes, int* tam);
void imprimeReticulado(listaLinhas* linhas, int tam);
void adicionarCelulaLinha(listaLinhas* linhas, nCelula* novaCelula);
void adicionarCelulaColuna(listaColunas* colunas, nCelula* novaCelula);

//funcoes auxiliares para verificacao de entrada de dados

void limparBuffer();
bool lerInteiro(int* valor);

//funcao auxiliar para desalocar todas as celulas de uma lista

void desalocarListaCelulas(nCelula* primeiraCelula);

#endif //final da especificacao de matriz.h
