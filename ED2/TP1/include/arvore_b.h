#ifndef ARVORE_B_H
#define ARVORE_B_H

#include <stdio.h>
#include <stdlib.h>
#include "registro.h"

#define ORDEM 5  // ordem m da arvore B (conforme slides)

typedef struct NoB {
    int num_chaves;                     // numero de chaves no no
    int chaves[2 * ORDEM - 1];          // chaves
    long posicoes[2 * ORDEM - 1];       // posicoes no arquivo
    long filhos[2 * ORDEM];      // ponteiros para filhos
    int folha;                          // indica se eh folha
} NoB;

// prototipos
NoB* criar_no_b(int folha);
void escrever_no(FILE* arq, NoB* no, long pos);
void ler_no(FILE* arq, NoB* no, long pos);
Registro* pesquisar_arvore_b(FILE* arq_arvore, FILE* arq_dados, long pos_no, int chave, int* transf, int* comp);
int inserir_arvore_b(FILE* arq_arvore, int* raiz_ind, int chave, long pos_dado);
#endif