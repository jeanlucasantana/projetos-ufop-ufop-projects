#include "sequencial_indexado.h"
#include <stdlib.h>

// criação do indice a partir do vetor de registros em memoria principal
IndicePagina* criar_indice_mp(Registro* vet, int total_reg, int* total_paginas, int* transf, int* comp){
    if (!vet || total_reg <= 0 || !total_paginas || !transf || !comp){
        return NULL;
    }

    *total_paginas = total_reg / REG_POR_PAGINA;
    if (total_reg % REG_POR_PAGINA){
        (*total_paginas)++;
    }

    IndicePagina* indice = (IndicePagina*) malloc((*total_paginas) * sizeof(IndicePagina));
    if (!indice){
        return NULL;
    }

    *transf = 0;
    *comp = 0;

    for (int i = 0; i < *total_paginas; i++){
        int pos_vet = i * REG_POR_PAGINA;

        if (pos_vet < total_reg){
            indice[i].chave   = vet[pos_vet].chave;
            indice[i].posicao = pos_vet;
            (*transf)++;  // acesso contado como transferencia logica
        } else{
            indice[i].chave   = 0;
            indice[i].posicao = pos_vet;
        }
    }

    return indice;
}
// pesquisa por chave no vetor usando acesso sequencial indexado em memoria principal
Registro* pesquisar_indexado_mp(Registro* vet, int total_reg, IndicePagina* indice, int total_pag, int chave, int* transf, int* comp){

    if (!vet || total_reg <= 0 || !indice || total_pag <= 0 || !transf || !comp){
        return NULL;
    }

    *transf = 0;
    *comp = 0;

    int l = 0, r = total_pag;
    while (l < r){
        (*comp)++;
        int mid = (l + r) / 2;
        if (indice[mid].chave <= chave){
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    int pagina_alvo = l - 1;
    if (pagina_alvo < 0 || pagina_alvo >= total_pag){
        return NULL;
    }

    int inicio = indice[pagina_alvo].posicao;
    int fim = inicio + REG_POR_PAGINA;
    if (fim > total_reg) fim = total_reg;

    int idx = inicio;
    while (idx < fim){
        (*transf)++;
        (*comp)++;
        if (vet[idx].chave == chave){
            Registro* resp = (Registro*) malloc(sizeof(Registro));
            if (!resp) return NULL;
            *resp = vet[idx];
            return resp;
        }
        idx++;
    }

    return NULL;
}

// liberacao do indice
void liberar_indice_mp(IndicePagina* indice){
    free(indice);
}