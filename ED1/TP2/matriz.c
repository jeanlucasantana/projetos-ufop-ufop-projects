#include "matriz.h"
#include "automato.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//funcao para leitura do reticulado

void leituraReticulado(listaLinhas* linhas, listaColunas* colunas, int* geracoes, int* tam){

    //verificacao para o tamanho do reticulado e do numero de geracoes

    printf("Digite o tamanho do reticulado e o numero de geracoes:\n");
    while(!lerInteiro(tam) || *tam <= 0 || !lerInteiro(geracoes) || *geracoes < 0){
        printf("Entrada invalida. Por favor, insira valores inteiros positivos para o tamanho do reticulado e nao negativos para o numero de geracoes:\n");
    }

    //inicializar as listas vazias

    alocarReticulado(linhas, colunas);

    //leitura dos valores do reticulado

    printf("Digite o reticulado inicial (%d linhas com %d colunas):\n",*tam, *tam);
    for(int i = 0; i < *tam; i++){
        for(int j = 0; j < *tam; j++){
            int valor; // variavel para conferir se o valor inserido pelo usuario esta correto
            while(!lerInteiro(&valor) || (valor != 0 && valor!= 1)){
                printf("Entrada invalida. Por favor, insira 0 ou 1 para a celula (%d, %d):\n", i, j);
            }
            if(valor == 1){ 

                //adicionar celula viva as listas
                nCelula* novaCelula = malloc(sizeof(nCelula));
                novaCelula -> celula.linha = i;
                novaCelula -> celula.coluna = j;
                novaCelula -> proximaLinha = NULL;
                novaCelula -> proximaColuna = NULL;

                adicionarCelulaLinha(linhas, novaCelula); // adiciona a nova celula na lista de linhas
                adicionarCelulaColuna(colunas, novaCelula); // adiciona a nova celula na lista de colunas
            }
        }
    }
}

//funcao para adicionar uma celula na lista de linhas

void adicionarCelulaLinha(listaLinhas* lista, nCelula* novaCelula){

    //duas variaveis auxiliares para ajudar na conexao das celulas

    nCelula* atual = lista -> primeiraLinha;
    nCelula* anterior = NULL;

    //percorre todas as celulas ate chegar na posicao apos a nova celula 

    while(atual != NULL && atual -> celula.coluna < novaCelula -> celula.coluna){
        anterior = atual;
        atual = atual -> proximaLinha;
    }

    //faz a nova celula apontar para a proxima

    novaCelula -> proximaLinha = atual;

    //caso anterior seja null significa que estamos na primeira celula

    if(anterior == NULL){
        lista -> primeiraLinha = novaCelula;
    }

    //senao fazemos a anterior apontar para a nova celula

    else{
        anterior -> proximaLinha = novaCelula;
    }
}

//funcao para adicionar uma celula na lista de colunas

void adicionarCelulaColuna(listaColunas* lista, nCelula* novaCelula){

    //duas variaveis auxiliares para ajudar na conexao das celulas

    nCelula* atual = lista -> primeiraColuna;
    nCelula* anterior = NULL;

    //percorre todas as celulas ate chegar na celula apos a nova celula

    while(atual != NULL && atual -> celula.linha < novaCelula -> celula.linha){
        anterior = atual;
        atual = atual -> proximaLinha;
    }

    //faz a nova celula apontar para a proxima

    novaCelula -> proximaColuna = atual;

    //caso anterior seja null significa que estamos na primeira celula

    if(anterior == NULL){
        lista -> primeiraColuna = novaCelula;
    }

    //senao fazemos a anterior apontar para a nova celula

    else{
        anterior -> proximaColuna = novaCelula;
    }
}

//funcao para alocar o reticulado

void alocarReticulado(listaLinhas* linhas, listaColunas* colunas){
    
    //inicializa as listas vazias(abordagem sem cabeca)

    linhas -> primeiraLinha = NULL;
    colunas -> primeiraColuna = NULL;
}

//funcao para imprimir as listas

void imprimeReticulado(listaLinhas* linhas, int tam) {
    // percorre cada linha 

    for (int i = 0; i < tam; i++){

        // para cada linha percorre as colunas 

        for (int j = 0; j < tam; j++){

            int encontrada = 0;  // variavel auxiliar para verificar se existe celula viva

            // verifica a lista de celulas vivas na linha atual

            nCelula* celulaLinha = linhas->primeiraLinha;
            while (celulaLinha != NULL) {
                //verifica se a celula atual da lista corresponde a celula (i, j)
                if (celulaLinha->celula.linha == i && celulaLinha->celula.coluna == j) {
                    encontrada = 1;  // a celula (i, j) foi encontrada
                    break;
                }
                celulaLinha = celulaLinha->proximaLinha;  // avanca para a proxima celula na linha
            }

            // imprime 1 se a célula (i, j) for encontrada, senao 0
            printf("%d ", encontrada);
        }
        printf("\n");
    }
}

//funcao para desalocar cada celula de uma lista
void desalocarListaCelulas(nCelula* primeiraCelula){
    while(primeiraCelula != NULL){
        nCelula *temp = primeiraCelula; //usa a variavel temp pra receber sempre a proxima celula pra desalocar
        primeiraCelula = primeiraCelula -> proximaLinha; //coloca a proxima celula na primeira posicao pra ir a temp e ser desalocada
        free(temp);
    }
}

//funcao para desalocar as listas

void desalocarReticulado(listaLinhas* linhas){

    //desaloca todas as listas, usando apenas uma ja que os elementos que estao em uma estao na outra //caso tentar desalocar as duas vai abortar por desalocacao da mesma memoria duas vezes

    desalocarListaCelulas(linhas -> primeiraLinha);

}


//funcao para limpar o buffer da entrada caso o valor inserido for diferente de um inteiro

void limparBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

//funcao para verificar se o valor da entrada e um numero inteiro 

bool lerInteiro(int* valor){
    int resultado = scanf("%d", valor);
    if(resultado != 1){
        limparBuffer();
    }
    return resultado == 1;
}