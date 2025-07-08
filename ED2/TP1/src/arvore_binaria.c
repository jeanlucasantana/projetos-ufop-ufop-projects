#include "arvore_binaria.h"

bool ArvoreBinaria(FILE *arq, int quantidade, int chave, bool print, Registro *item, int *transferencias, int*comparacoes)
{
    *transferencias = 0;
    *comparacoes = 0;

    // cria (ou sobrescreve) o arquivo da ABP
    FILE *arqAbp = fopen("abp.bin", "wb+");
    if (arqAbp == NULL) {
        perror("nao foi possível abrir o arquivo ABP");
        return false;
    }

    // constroi a arvore no arquivo externo
    constroiArvore(arq, arqAbp, quantidade, transferencias, comparacoes);

    // se pediu pra imprimir, faz isso agora
    if (print) {
        printf("\nChaves do arquivo:\n");
        imprimeAbp(arqAbp, 0);
        printf("\n");
    }

    // pesquisa o item na árvore
    bool encontrado = pesquisarAbp(arqAbp, chave, item, transferencias, comparacoes);

    fclose(arqAbp);
    return encontrado;
}

void insereNaArvore(FILE *arqAbp, Registro itemInserir, int *transferencias, int *comparacoes)
{
    tipoNo novoItem;
    novoItem.item = itemInserir;
    novoItem.esq = -1;
    novoItem.dir = -1;

    fseek(arqAbp, 0, SEEK_END);
    long posicaoInserir = ftell(arqAbp);
    fwrite(&novoItem, sizeof(tipoNo), 1, arqAbp);
    *transferencias += 2;

    if (posicaoInserir == 0)
        return;

    long ponteiro = 0;

    while (true) {
        if (ponteiro == -1) break; // posicao invalida, fim do percurso

        fseek(arqAbp, ponteiro * sizeof(tipoNo), SEEK_SET);
        (*transferencias)++;
        tipoNo aux;
        if (fread(&aux, sizeof(tipoNo), 1, arqAbp) != 1) break;
        (*transferencias)++;

        (*comparacoes)++;
        if (itemInserir.chave < aux.item.chave) {
            if (aux.esq == -1) {
                aux.esq = posicaoInserir / sizeof(tipoNo);
                fseek(arqAbp, -sizeof(tipoNo), SEEK_CUR);
                fwrite(&aux, sizeof(tipoNo), 1, arqAbp);
                *transferencias += 2;
                break;
            }
            ponteiro = aux.esq;
        } else {
            if (aux.dir == -1) {
                aux.dir = posicaoInserir / sizeof(tipoNo);
                fseek(arqAbp, -sizeof(tipoNo), SEEK_CUR);
                fwrite(&aux, sizeof(tipoNo), 1, arqAbp);
                *transferencias += 2;
                break;
            }
            ponteiro = aux.dir;
        }
    }
}

void constroiArvore(FILE *arq, FILE *arqAbp, int quantidade, int *transferencias, int *comparacoes)
{
    Registro itemLeitura;
    int cont = 0;

    while (fread(&itemLeitura, sizeof(Registro), 1, arq) == 1 && cont < quantidade) {
        (*transferencias)++;
        insereNaArvore(arqAbp, itemLeitura, transferencias, comparacoes);
        cont++;
    }
}

bool pesquisarAbp(FILE *arqAbp, int chave, Registro *item, int *transferencias, int *comparacoes)
{
    tipoNo aux;
    long ponteiro = 0;

    while (ponteiro != -1) {
        if (fseek(arqAbp, ponteiro * sizeof(tipoNo), SEEK_SET) != 0) break;
        (*transferencias)++;
        if (fread(&aux, sizeof(tipoNo), 1, arqAbp) != 1) break;
        (*transferencias)++;

        (*comparacoes)++;
        if (aux.item.chave == chave) {
            *item = aux.item;
            return true;
        }
        (*comparacoes)++;
        ponteiro = (chave > aux.item.chave) ? aux.dir : aux.esq;
    }

    return false;
}

void imprimeAbp(FILE *arqAbp, long ponteiro)
{
    if (ponteiro == -1) return;

    tipoNo aux;
    fseek(arqAbp, ponteiro * sizeof(tipoNo), SEEK_SET);

    if (fread(&aux, sizeof(tipoNo), 1, arqAbp) != 1) return;

    imprimeAbp(arqAbp, aux.esq);
    printf("%d ", aux.item.chave);
    imprimeAbp(arqAbp, aux.dir);
}
