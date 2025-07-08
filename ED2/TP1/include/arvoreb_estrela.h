#include <stdio.h>
#include "registro.h"
#include <stdbool.h>

// --- DEFINIÇÕES GLOBAIS E ESTRUTURAS ---

// Ordem da árvore. M = número mínimo de chaves em um nó (exceto raiz).
#define M 4
#define MM (4 * M)

// Estrutura para a página (nó) da árvore
typedef struct Pagina *Apontador;
typedef struct Pagina
{
    bool tipo; // true: INTERNA, false: EXTERNA (folha)
    int n;     // Número de chaves/registros no nó
    union
    {
        // Nós internos
        struct
        {
            int chaves_internas[MM];
            Apontador filhos[MM + 1];
        } interna;
        // Nós externos (folhas)
        struct
        {
            Registro registros[MM];
        } externa;
    } UU;
} Pagina;
// --- PROTÓTIPOS DAS FUNÇÕES ---

// Funções principais
bool executar_arvore_b_estrela(FILE *arquivo, int quantidade, int chave, bool print, Registro *item, int *transferencias, int *comparacoes);
void carregar_do_arquivo(int qtd, FILE *arquivo, Apontador *arvore);

// Funções da Árvore B*
void inicializar_arvore(Apontador *arvore);
void pesquisar(int chave, Registro *x, Apontador ap);
void insere(Registro reg, Apontador *ap);
void insere_recursivo(Registro reg, Apontador ap, bool *cresceu, Registro *reg_retorno, Apontador *ap_retorno);
void insere_na_pagina(Apontador ap, Registro reg, Apontador ap_dir);
void liberar_arvore(Apontador arvore);
void imprimir_arvore(Apontador arvore, int nivel);