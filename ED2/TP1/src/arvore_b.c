#include "arvore_b.h"
#include "inserir_arvore_b.h"
#include <string.h>
#include <stdlib.h>

// cria um novo no em memória
NoB* criar_no_b(int folha) {
    NoB* no = (NoB*) malloc(sizeof(NoB));
    no->num_chaves = 0;
    no->folha = folha;

    for (int i = 0; i < 2 * ORDEM - 1; i++) {
        no->chaves[i] = 0;
        no->posicoes[i] = -1;
    }

    for (int i = 0; i < 2 * ORDEM; i++) {
        no->filhos[i] = -1; // -1 indica que nao ha filho
    }

    return no;
}

// escreve um no no arquivo da arvore na posição pos
void escrever_no(FILE* arq, NoB* no, long pos) {
    fseek(arq, pos * sizeof(NoB), SEEK_SET);
    fwrite(no, sizeof(NoB), 1, arq);
}

// le um no do arquivo da arvore na posição 'pos'
void ler_no(FILE* arq, NoB* no, long pos) {
    fseek(arq, pos * sizeof(NoB), SEEK_SET);
    fread(no, sizeof(NoB), 1, arq);
}

// pesquisa uma chave a partir da posicao da raiz no arquivo
Registro* pesquisar_arvore_b(FILE* arq_arvore, FILE* arq_dados, long pos_no, int chave, int* transf, int* comp) {
    if (pos_no == -1) return NULL;

    NoB no;
    ler_no(arq_arvore, &no, pos_no);
    (*transf)++;

    int i = 0;
    while (i < no.num_chaves && chave > no.chaves[i]) {
        (*comp)++;
        i++;
    }

    if (i < no.num_chaves) {
        (*comp)++; 
        if (chave == no.chaves[i]) {
            // encontrou a chave
            fseek(arq_dados, no.posicoes[i], SEEK_SET);
            Registro* reg = (Registro*) malloc(sizeof(Registro));
            fread(reg, sizeof(Registro), 1, arq_dados);
            (*transf)++;
            return reg;
        }
    }

    // se for folha e não achou, acabou
    if (no.folha) return NULL;

    // busca no filho correspondente
    return pesquisar_arvore_b(arq_arvore, arq_dados, no.filhos[i], chave, transf, comp);
}

//funcao principal para criar a arvore b

int inserir_arvore_b(FILE* arq_arvore, int* raiz_ind, int chave, long pos_dado) {
    NoB raiz;
    ler_no_indexado(arq_arvore, &raiz, *raiz_ind);

    if (raiz.num_chaves == 2 * ORDEM - 1) {
        NoB nova_raiz = *criar_no_b(0);          // folha = 0: raiz não é folha
        nova_raiz.filhos[0] = *raiz_ind;         // antiga raiz vira filho 0 da nova raiz

        int nova_raiz_ind = alocar_novo_no(arq_arvore, &nova_raiz); // grava nova raiz no arquivo

        dividir_filho(arq_arvore, nova_raiz_ind, 0, *raiz_ind); // divide a antiga raiz (filho 0)

        inserir_nao_cheio(arq_arvore, nova_raiz_ind, chave, pos_dado); // insere no novo nó

        *raiz_ind = nova_raiz_ind;                // atualiza raiz para nova raiz
    } else {
        inserir_nao_cheio(arq_arvore, *raiz_ind, chave, pos_dado);
    }

    return 1;
}
