#ifndef INSERIR_ARVORE_B_H
#define INSERIR_ARVORE_B_H

#include <stdio.h>
#include "arvore_b.h"

int alocar_novo_no(FILE* arq, NoB* no);
void escrever_no_indexado(FILE* arq, NoB* no, int indice);
void ler_no_indexado(FILE* arq, NoB* no, int indice);
void dividir_filho(FILE* arq, int pai_ind, int i, int filho_cheio_ind);
void inserir_nao_cheio(FILE* arq_arvore, int no_ind, int chave, long pos_dado);

#endif