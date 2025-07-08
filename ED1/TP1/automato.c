#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "automato.h"


Reticulado* alocarReticulado(int tamanho, int geracoes){
    Reticulado* reticulado = (Reticulado*)malloc(sizeof(Reticulado));
    reticulado -> tamanho = tamanho;
    reticulado -> geracoes = geracoes;
    reticulado -> reticulado = (int**)malloc(tamanho * sizeof(int*));
    for(int i = 0; i < tamanho; i++){
        reticulado  -> reticulado[i] = (int*)malloc(tamanho * sizeof(int));
    }
    return reticulado;
}

void desalocarReticulado(Reticulado* reticulado){
    for(int i = 0; i < reticulado->tamanho; i++){
        free(reticulado->reticulado[i]);
    }
    free(reticulado->reticulado);
    free(reticulado);
}

Reticulado* LeituraReticulado(int* tamanho, int* geracoes){
    printf("Digite o tamanho do reticulado e o numero de geracoes:\n");
    while(!lerInteiro(tamanho) || *tamanho <= 0 || !lerInteiro(geracoes) || *geracoes < 0){
        printf("Entrada invalida. Por favor, insira valores inteiros positivos para o tamanho do reticulado e nao negativos para o numero de geracoes:\n");
    }

    Reticulado* reticulado = alocarReticulado(*tamanho, *geracoes);

    printf("Digite o reticulado inicial (%d linhas com %d colunas):\n", *tamanho, *tamanho);
    for(int i = 0; i < *tamanho; i++){
        for(int j = 0; j < *tamanho; j++){
            while(!lerInteiro(&reticulado -> reticulado[i][j]) || (reticulado -> reticulado[i][j] != 0 && reticulado -> reticulado[i][j] != 1)){
                printf("Entrada invalida. Por favor, insira 0 ou 1 para a celula (%d, %d):\n", i, j);
            }
        }
    }
    return reticulado;
}

void imprimeReticulado(Reticulado* reticulado){
    for(int i = 0; i < reticulado -> tamanho; i++){
        for(int j = 0; j < reticulado -> tamanho; j++){
            printf("%d ", reticulado -> reticulado[i][j]);
        }
        printf("\n");
    }
}

void limparBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

bool lerInteiro(int* valor){
    int resultado = scanf("%d", valor);
    if(resultado != 1){
        limparBuffer();
    }
    return resultado == 1;
}

int contarVizinhosVivos(Reticulado* reticulado, int linha, int coluna){
    int vizinhosVivos = 0;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <=1; j++){
            if(i == 0 && j == 0)continue;
            int novaLinha = linha + i;
            int novaColuna = coluna + j;
            if(novaLinha >= 0 && novaLinha < reticulado -> tamanho && novaColuna >= 0 && novaColuna < reticulado -> tamanho){
                vizinhosVivos += reticulado -> reticulado[novaLinha][novaColuna];
            }
        }
    }
    return vizinhosVivos;
}

void evoluirReticulado(Reticulado* reticuladoAtual, Reticulado* novoReticulado, int tamanho, int geracaoAtual, int geracoes){
    if(geracaoAtual == geracoes) return;

    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            int vizinhosVivos = contarVizinhosVivos(reticuladoAtual, i, j);
            if(reticuladoAtual -> reticulado[i][j] == 1){
                novoReticulado -> reticulado[i][j] = (vizinhosVivos == 2 || vizinhosVivos == 3) ? 1 : 0;
            }
            else{
                novoReticulado -> reticulado[i][j] = (vizinhosVivos == 3) ? 1 : 0;
            }
        }
    }

    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            reticuladoAtual -> reticulado[i][j] = novoReticulado -> reticulado[i][j];
        }
    }

    evoluirReticulado(reticuladoAtual, novoReticulado, tamanho, geracaoAtual + 1, geracoes);
}

















