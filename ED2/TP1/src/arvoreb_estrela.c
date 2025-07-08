#include "arvoreb_estrela.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "registro.h"

// variaveis globais para estatisticas
extern long transferencias;
extern long comparacoes;

bool executar_arvore_b_estrela(FILE *arquivo, int quantidade, int chave, bool print, Registro *item, int *transferencias_out, int *comparacoes_out) {
    Apontador arvore;
    inicializar_arvore(&arvore);

    transferencias = 0;
    comparacoes = 0;
    carregar_do_arquivo(quantidade, arquivo, &arvore);
    *transferencias_out = transferencias;
    *comparacoes_out = comparacoes;

    transferencias = 0;
    comparacoes = 0;

    if (print) {
        printf("\n--- Estrutura da Arvore B* ---\n");
        imprimir_arvore(arvore, 0);
        printf("\n-----------------------------\n");
    }

    pesquisar(chave, item, arvore);

    *transferencias_out += transferencias;
    *comparacoes_out += comparacoes;

    liberar_arvore(arvore);

    return item->chave == chave;
}

void carregar_do_arquivo(int qtd, FILE *arquivo, Apontador *arvore) {
    Registro reg;
    rewind(arquivo);
    int cont = 0;

    while (fread(&reg, sizeof(Registro), 1, arquivo) == 1 && cont < qtd) {
        transferencias++;
        insere(reg, arvore);
        cont++;
    }
}

void inicializar_arvore(Apontador *arvore) {
    *arvore = NULL;
}

void pesquisar(int chave, Registro *x, Apontador ap) {
    if (ap == NULL) {
        x->chave = -1;
        return;
    }

    transferencias++;

    if (ap->tipo == true) {
        int i = 0;
        while (i < ap->n && chave > ap->UU.interna.chaves_internas[i]) {
            comparacoes++;
            transferencias++;
            i++;
        }
        comparacoes++;
        transferencias++;
        pesquisar(chave, x, ap->UU.interna.filhos[i]);
    } else {
        int i = 0;
        while (i < ap->n && chave > ap->UU.externa.registros[i].chave) {
            comparacoes++;
            transferencias++;
            i++;
        }
        comparacoes++;
        if (i < ap->n && chave == ap->UU.externa.registros[i].chave) {
            *x = ap->UU.externa.registros[i];
            transferencias++;
        } else {
            x->chave = -1;
        }
    }
}

void insere(Registro reg, Apontador *ap) {
    bool cresceu;
    Registro reg_retorno;
    Apontador ap_retorno, ap_temp;

    if (*ap == NULL) {
        ap_temp = (Apontador)malloc(sizeof(Pagina));
        ap_temp->tipo = false;
        ap_temp->n = 1;
        ap_temp->UU.externa.registros[0] = reg;
        *ap = ap_temp;
        return;
    }

    insere_recursivo(reg, *ap, &cresceu, &reg_retorno, &ap_retorno);

    if (cresceu) {
        ap_temp = (Apontador)malloc(sizeof(Pagina));
        ap_temp->tipo = true;
        ap_temp->n = 1;
        ap_temp->UU.interna.chaves_internas[0] = reg_retorno.chave;
        ap_temp->UU.interna.filhos[0] = *ap;
        ap_temp->UU.interna.filhos[1] = ap_retorno;
        *ap = ap_temp;
    }
}

void insere_recursivo(Registro reg, Apontador ap, bool *cresceu, Registro *reg_retorno, Apontador *ap_retorno) {
    int i;
    Apontador ap_temp;

    if (ap->tipo == false) {
        Registro temp[MM + 1];
        int i = 0;

        // copia os registros existentes e insere o novo na posição correta
        while (i < ap->n && reg.chave > ap->UU.externa.registros[i].chave) {
            temp[i] = ap->UU.externa.registros[i];
            i++;
            }

        int pos = i;
        temp[i++] = reg;

        while (i <= ap->n) {
            temp[i] = ap->UU.externa.registros[i - 1];
            i++;
        }

        // nao precisa comparar se a chave já existe aqui, pois não eh foco

        if (ap->n < MM) {
            // insercao direta sem split
            for (int j = ap->n; j > pos; j--)
            ap->UU.externa.registros[j] = ap->UU.externa.registros[j - 1];

            ap->UU.externa.registros[pos] = reg;
            ap->n++;
            *cresceu = false;
            return;
        }

    // split necessario
    ap_temp = (Apontador)malloc(sizeof(Pagina));
    ap_temp->tipo = false;

    int meio = (MM + 1) / 2;

    ap->n = meio;
    ap_temp->n = (MM + 1) - meio;

    for (int j = 0; j < meio; j++)
        ap->UU.externa.registros[j] = temp[j];

    for (int j = 0; j < ap_temp->n; j++)
        ap_temp->UU.externa.registros[j] = temp[meio + j];

    *reg_retorno = ap_temp->UU.externa.registros[0];
    *ap_retorno = ap_temp;
    *cresceu = true;
    return;
}

    i = 0;
    while (i < ap->n && reg.chave > ap->UU.interna.chaves_internas[i]) {
        comparacoes++;
        transferencias++;
        i++;
    }
    comparacoes++;

    insere_recursivo(reg, ap->UU.interna.filhos[i], cresceu, reg_retorno, ap_retorno);

    if (!*cresceu) return;

    if (ap->n < MM) {
        insere_na_pagina(ap, *reg_retorno, *ap_retorno);
        *cresceu = false;
        return;
    }

    ap_temp = (Apontador)malloc(sizeof(Pagina));
    ap_temp->tipo = true;
    ap_temp->n = 0;
    Registro reg_mediano;

    if (i > M)
        insere_na_pagina(ap_temp, *reg_retorno, *ap_retorno);
    else {
        insere_na_pagina(ap_temp, (Registro){ap->UU.interna.chaves_internas[MM - 1]}, ap->UU.interna.filhos[MM]);
        ap->n--;
        insere_na_pagina(ap, *reg_retorno, *ap_retorno);
    }

    for (int j = M + 1; j < MM; j++) {
        insere_na_pagina(ap_temp, (Registro){ap->UU.interna.chaves_internas[j]}, ap->UU.interna.filhos[j + 1]);
        transferencias++;
    }

    reg_mediano.chave = ap->UU.interna.chaves_internas[M];
    ap->n = M;
    ap_temp->UU.interna.filhos[0] = ap->UU.interna.filhos[M + 1];

    *cresceu = true;
    *reg_retorno = reg_mediano;
    *ap_retorno = ap_temp;
}

void insere_na_pagina(Apontador ap, Registro reg, Apontador ap_dir) {
    int i = ap->n;
    if (ap->tipo == false) {
        while (i > 0 && reg.chave < ap->UU.externa.registros[i - 1].chave) {
            comparacoes++;
            ap->UU.externa.registros[i] = ap->UU.externa.registros[i - 1];
            transferencias++;
            i--;
        }
        comparacoes++;
        ap->UU.externa.registros[i] = reg;
        transferencias++;
    } else {
        while (i > 0 && reg.chave < ap->UU.interna.chaves_internas[i - 1]) {
            comparacoes++;
            ap->UU.interna.chaves_internas[i] = ap->UU.interna.chaves_internas[i - 1];
            ap->UU.interna.filhos[i + 1] = ap->UU.interna.filhos[i];
            transferencias += 2;
            i--;
        }
        comparacoes++;
        ap->UU.interna.chaves_internas[i] = reg.chave;
        ap->UU.interna.filhos[i + 1] = ap_dir;
        transferencias += 2;
    }
    ap->n++;
}

void liberar_arvore(Apontador arvore) {
    if (arvore == NULL) return;
    if (arvore->tipo == true) {
        for (int i = 0; i <= arvore->n; i++)
            liberar_arvore(arvore->UU.interna.filhos[i]);
    }
    free(arvore);
}

void imprimir_arvore(Apontador arvore, int nivel) {
    if (arvore == NULL) return;
    for (int i = 0; i < nivel; i++) printf("  ");
    if (arvore->tipo == false) {
        printf("Folha: ");
        for (int i = 0; i < arvore->n; i++)
            printf("%d ", arvore->UU.externa.registros[i].chave);
        printf("\n");
    } else {
        printf("Interno: ");
        for (int i = 0; i < arvore->n; i++)
            printf("%d ", arvore->UU.interna.chaves_internas[i]);
        printf("\n");
        for (int i = 0; i <= arvore->n; i++)
            imprimir_arvore(arvore->UU.interna.filhos[i], nivel + 1);
    }
}
