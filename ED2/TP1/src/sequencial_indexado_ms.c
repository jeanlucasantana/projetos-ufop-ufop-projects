#include "sequencial_indexado_ms.h"
#include <stdlib.h>

// verifica se o arquivo esta ordenado (crescente) pelas chaves
int arquivo_ordenado_ms(FILE* arq) {
    if (!arq) return 0;

    Registro reg_ant, reg_at;
    if (fread(&reg_ant, sizeof(Registro), 1, arq) != 1) {
        rewind(arq);
        return 1;  // arquivo vazio considera ordenado
    }

    while (fread(&reg_at, sizeof(Registro), 1, arq) == 1) {
        if (reg_at.chave < reg_ant.chave) {
            rewind(arq);
            return 0;
        }
        reg_ant = reg_at;
    }

    rewind(arq);
    return 1;
}

// cria o indice para acesso sequencial indexado em memoria secundaria
IndicePagina* criar_indice_ms(FILE* arq, int total_reg, int* total_paginas, int* transf, int* comp){

    if (!arq || total_reg <= 0 || !total_paginas || !transf || !comp) {
        return NULL;
    }
    *total_paginas = total_reg / REG_POR_PAGINA;
    if (total_reg % REG_POR_PAGINA) {
        (*total_paginas)++;
    }
    IndicePagina* indice = (IndicePagina*) malloc((*total_paginas) * sizeof(IndicePagina));
    if (!indice) {
        rewind(arq);
        return NULL;
    }
    *transf = 0;
    *comp   = 0;
    for (int i = 0; i < *total_paginas; i++) {
        long pos = ftell(arq);
        Registro reg;

        if (fread(&reg, sizeof(Registro), 1, arq) != 1) {
            free(indice);
            rewind(arq);
            return NULL;
        }

        (*transf)++;
        indice[i].chave   = reg.chave;
        indice[i].posicao = pos;

        if (i < (*total_paginas) - 1) {
            fseek(arq, (REG_POR_PAGINA - 1) * sizeof(Registro), SEEK_CUR);
        }
    }

    rewind(arq);
    return indice;
}

// pesquisa por chave usando acesso sequencial indexado na memoria secundaria
Registro* pesquisar_indexado_ms(FILE* arq, IndicePagina* indice, int total_pag, int chave, int* transf, int* comp)
{
    if (!arq || !indice || total_pag <= 0 || !transf || !comp) {
        return NULL;
    }

    *transf = 0;
    *comp   = 0;

    // busca binaria no indice
    int l = 0, r = total_pag;
    while (l < r) {
        (*comp)++;
        int mid = (l + r) / 2;
        if (indice[mid].chave <= chave) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    int pagina_alvo = l - 1;
    if (pagina_alvo < 0 || pagina_alvo >= total_pag || indice[pagina_alvo].posicao < 0) {
        return NULL;
    }

    if (fseek(arq, indice[pagina_alvo].posicao, SEEK_SET) != 0) {
        return NULL;
    }

    Registro* buffer = (Registro*) malloc(REG_POR_PAGINA * sizeof(Registro));
    if (!buffer) {
        return NULL;
    }

    int lidos = fread(buffer, sizeof(Registro), REG_POR_PAGINA, arq);
    (*transf) += lidos;

    int j = 0;
    while (j < lidos) {
        (*comp)++;
        if (buffer[j].chave == chave) {
            Registro* resp = (Registro*) malloc(sizeof(Registro));
            if (!resp) {
                free(buffer);
                return NULL;
            }
            *resp = buffer[j];
            free(buffer);
            return resp;
        }
        j++;
    }

    free(buffer);
    return NULL;
}

// libera o indice criado
void liberar_indice_ms(IndicePagina* indice) {
    free(indice);
}