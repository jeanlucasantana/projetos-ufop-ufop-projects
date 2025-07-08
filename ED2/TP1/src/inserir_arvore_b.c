#include "arvore_b.h"
#include <string.h>
#include <stdlib.h>

// variavel global simples para indice de nos
static int prox_indice_no = 0;

// alocar um novo no na arvore
int alocar_novo_no(FILE* arq, NoB* no) {
    int indice = prox_indice_no++;
    fseek(arq, indice * sizeof(NoB), SEEK_SET);
    fwrite(no, sizeof(NoB), 1, arq);
    return indice;
}

//escreve em determinado no na arvore b
void escrever_no_indexado(FILE* arq, NoB* no, int indice) {
    fseek(arq, indice * sizeof(NoB), SEEK_SET);
    fwrite(no, sizeof(NoB), 1, arq);
}

//le um no da arvore b
void ler_no_indexado(FILE* arq, NoB* no, int indice) {
    fseek(arq, indice * sizeof(NoB), SEEK_SET);
    fread(no, sizeof(NoB), 1, arq);
}

//funcao para dividir um filho cheio da arvore b
void dividir_filho(FILE* arq, int pai_ind, int i, int filho_cheio_ind) {
    NoB pai, filho_cheio, novo_no;
    ler_no_indexado(arq, &pai, pai_ind);
    ler_no_indexado(arq, &filho_cheio, filho_cheio_ind);

    novo_no = *criar_no_b(filho_cheio.folha);
    novo_no.num_chaves = ORDEM - 1;

    for (int j = 0; j < ORDEM - 1; j++) {
        novo_no.chaves[j] = filho_cheio.chaves[j + ORDEM];
        novo_no.posicoes[j] = filho_cheio.posicoes[j + ORDEM];
    }

    if (!filho_cheio.folha) {
        for (int j = 0; j < ORDEM; j++) {
            novo_no.filhos[j] = filho_cheio.filhos[j + ORDEM];
        }
    }

    filho_cheio.num_chaves = ORDEM - 1;

    int novo_ind = alocar_novo_no(arq, &novo_no);  // Já escreve o novo_no no arquivo

    for (int j = pai.num_chaves; j >= i + 1; j--)
        pai.filhos[j + 1] = pai.filhos[j];

    pai.filhos[i + 1] = novo_ind;

    for (int j = pai.num_chaves - 1; j >= i; j--) {
        pai.chaves[j + 1] = pai.chaves[j];
        pai.posicoes[j + 1] = pai.posicoes[j];
    }

    pai.chaves[i] = filho_cheio.chaves[ORDEM - 1];
    pai.posicoes[i] = filho_cheio.posicoes[ORDEM - 1];
    pai.num_chaves++;

    escrever_no_indexado(arq, &filho_cheio, filho_cheio_ind);
    escrever_no_indexado(arq, &pai, pai_ind);

    printf("[DIVIDIR] pai_ind = %d | num_chaves = %d\n", pai_ind, pai.num_chaves);
    printf("[DIVIDIR] filhos: ");
    for (int k = 0; k <= pai.num_chaves; k++) {
        printf("%ld ", pai.filhos[k]);
    }
    printf("\n");
}

//Funcao para inserir chaves na arvore b
void inserir_nao_cheio(FILE* arq_arvore, int no_ind, int chave, long pos_dado) {
    NoB no;
    ler_no_indexado(arq_arvore, &no, no_ind);
    //printf("[INSERÇÃO] Início - Nó %d | num_chaves = %d | chave = %d | folha = %d\n", no_ind, no.num_chaves, chave, no.folha);

    int i = no.num_chaves - 1;

    if (no.folha) {
        //printf("[INSERÇÃO] Nó %d é folha. Inserindo...\n", no_ind);
        while (i >= 0 && chave < no.chaves[i]) {
            no.chaves[i + 1] = no.chaves[i];
            no.posicoes[i + 1] = no.posicoes[i];
            i--;
        }
        no.chaves[i + 1] = chave;
        no.posicoes[i + 1] = pos_dado;
        no.num_chaves++;
        //printf("[INSERÇÃO] Inserida chave %d na posição %d do nó %d (folha). Novo num_chaves = %d\n", chave, i + 1, no_ind, no.num_chaves);
        escrever_no_indexado(arq_arvore, &no, no_ind);
    } else {
        while (i >= 0 && chave < no.chaves[i]) {
            i--;
        }
        i++;
        //printf("[INSERÇÃO] Nó %d não é folha. Vai inserir no filho %d (índice filho = %ld)\n", no_ind, i, no.filhos[i]);

        NoB filho;
        ler_no_indexado(arq_arvore, &filho, no.filhos[i]);
        //printf("[INSERÇÃO] Filho %ld tem %d chaves\n", no.filhos[i], filho.num_chaves);

        if (filho.num_chaves == 2 * ORDEM - 1) {
            //printf("[INSERÇÃO] Filho %ld está cheio. Dividindo filho...\n", no.filhos[i]);
            dividir_filho(arq_arvore, no_ind, i, no.filhos[i]);
            ler_no_indexado(arq_arvore, &no, no_ind);
            if (chave > no.chaves[i]) {
                i++;
                //printf("[INSERÇÃO] Após divisão, chave %d > chave promovida %d. Indo para filho %d\n", chave, no.chaves[i - 1], i);
            }
        }

        inserir_nao_cheio(arq_arvore, no.filhos[i], chave, pos_dado);
    }

   //printf("[INSERÇÃO] Fim da chamada para nó %d\n", no_ind);
}