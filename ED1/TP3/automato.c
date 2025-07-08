#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "automato.h"
#include "double_hash.h"


Reticulado* alocarReticulado(int tamanho, int geracoes){
    Reticulado* reticulado = (Reticulado*)malloc(sizeof(Reticulado)); //alocando memoria para toda a estrutura reticulado
    if(reticulado == NULL){
        return NULL;//tratamento de erro
    }
    reticulado -> linhas = tamanho; //atribuindo o tamanho das linhas do reticulado
    reticulado -> colunas = tamanho; //atribuindo o tamanho das colunas do reticulado
    reticulado -> geracoes = geracoes; //atribuindo numero de geracoes do reticulado 
    reticulado -> tamanhoTotal = (tamanho * tamanho) * 2 ; //atribuindo o tamanho total do reticulado 
    reticulado -> reticulado = (Celula*)malloc(reticulado -> tamanhoTotal * sizeof(Celula)); //alocando memoria para o reticulado
    if(reticulado -> reticulado == NULL){
        free(reticulado);
        return NULL;//tratamento de erro
    }
    for(int i = 0; i < reticulado -> tamanhoTotal; i++){
        reticulado -> reticulado[i].valor = -1;//inicializando o valor das celulas como vazio
        reticulado -> reticulado[i].x = -1;//inicializando o valor da coordenada como vazio
        reticulado -> reticulado[i].y = -1;//inicializando o valor da coordenada como vazio
    }
    return reticulado; //retornando a memoria necessaria para uma estrutura reticulado
}

void desalocarReticulado(Reticulado* reticulado){
    if(reticulado != NULL){
        free(reticulado -> reticulado);//desaloca o vetor de celulas
        free(reticulado);//desaloca toda a estrutura do reticulado
    }
}

void limparBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);//limpa a entrada enquanto nao for uma quebra de linha ou final de linha
}

bool lerInteiro(int* valor){
    int resultado = scanf("%d", valor);//recebe o inteiro de determinada variavel
    if(resultado != 1){
        limparBuffer();//limpa a entrada caso a entrada seja diferente de um numero
    }
    return resultado == 1;//se a entrada for um inteiro valido retorna 1
}

Reticulado* leituraReticulado(int* tamanho, int* geracoes){
    //printf("Digite o tamanho do reticulado e o numero de geracoes:\n");//recebendo o tamanho do reticulado e o numero de geracoes
    while(!lerInteiro(tamanho) || *tamanho <= 0 || !lerInteiro(geracoes) || *geracoes < 0){
        //printf("Entrada invalida. Por favor, insira valores inteiros positivos para o tamanho do reticulado e nao negativos para o numero de geracoes:\n");
    }

    Reticulado* reticulado = alocarReticulado(*tamanho, *geracoes);//aloca a memoria necessaria para a estrutura
    //imprimeReticulado(reticulado);

    //printf("Digite o reticulado inicial (%d linhas com %d colunas):\n", *tamanho, *tamanho);//recebendo as informacoes das celulas
    for(int i = 0; i < *tamanho; i++){
        for(int j = 0; j < *tamanho; j++){
            int valor;//variavel para verificacao do valor da celula
            while(!lerInteiro(&valor) || (valor != 0 && valor != 1)){
                //printf("Entrada invalida. Por favor, insira 0 ou 1 para a celula (%d %d):\n", i, j);
            }
            inserirHash(reticulado, i, j, valor);//inserindo os valores no reticulado
        }
    }
    return reticulado;//retornamos a estrutura  
}

void imprimeReticulado(Reticulado* reticulado){
    for(int i = 0; i < reticulado -> linhas; i++){
        for(int j = 0; j < reticulado -> colunas; j++){
            int indice = pesquisarCelula(reticulado, i, j);//acha o elemento desejado
            if(indice != -1){
                printf("%d ", reticulado -> reticulado[indice].valor);
            }
            else{
                printf("-2 ");//representa que o elemento nao foi armazenado corretamente
            }
        }
        printf("\n");//pula a linha
    }
}

int contarVizinhosVivos(Reticulado* reticulado, int linhas, int colunas) {
    if (reticulado == NULL) {
        //printf("Erro: reticulado nulo\n");
        return 0;
    }
    int vizinhosVivos = 0;//inicializa a variavel auxiliar de vizinhos vivos
    //percorre as posicoes vizinhas
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            //ignora a propria celula
            if (i == 0 && j == 0) {
                continue;
            }
            int novaLinha = linhas + i;
            int novaColuna = colunas + j;
            //verifica se a posicao esta dentro dos limites do tabuleiro
            if (novaLinha >= 0 && novaLinha < reticulado->linhas && novaColuna >= 0 && novaColuna < reticulado->colunas) {
                int indice = pesquisarCelula(reticulado, novaLinha, novaColuna);//pesquisa a celula a ser comparada
                //verifica se o endereco esta vazio e se o valor da celula esta vivo
                if (indice != -1 && reticulado->reticulado[indice].valor == 1) {
                    vizinhosVivos++;//incrementa a variavel auxiliar caso a celula esteja viva
                }
            }
        }
    }
    return vizinhosVivos;//retorna o numero de vizinhos vivos para determinada celula
}

void evoluirReticulado(Reticulado** reticulado){
    // Cria uma cópia do reticulado atual para calcular a próxima geração
    Reticulado* novoReticulado = alocarReticulado((*reticulado)->linhas, (*reticulado)->geracoes);
    //printf("debug");
    //for(int i = 0; i < novoReticulado -> tamanhoTotal; i++){
        //printf("%d %d %d\n", novoReticulado -> reticulado[i].x, novoReticulado -> reticulado[i].y, novoReticulado ->reticulado[i].valor);
    //}
    //imprimeReticulado(novoReticulado);
    //printf("debug");
    for (int i = 0; i < (*reticulado)->linhas; i++) {
        for (int j = 0; j < (*reticulado)->colunas; j++) {
            //printf("debug");
            int vizinhosVivos = contarVizinhosVivos(*reticulado, i, j);//conta os vizinhos vivos
            int indice = pesquisarCelula(*reticulado, i, j); // obtem o indice da celula no reticulado original
            //printf("Processando celula (%d, %d), indice: %d, vizinhos vivos: %d\n", i, j, indice, vizinhosVivos);
            //verifica indice valido
            if (indice == -1) {
                //printf("Erro: indice para celula (%d, %d) invalido\n", i, j);
                continue; // Pula esta célula, pois o índice está incorreto
            }
            //regras para celulas vivas
            if ((*reticulado)->reticulado[indice].valor == 1) {
                if (vizinhosVivos == 2 || vizinhosVivos == 3) {
                    novoReticulado -> reticulado[indice].x =
                    novoReticulado->reticulado[indice].valor = 1; //sobrevive
                } else {
                    novoReticulado->reticulado[indice].valor = 0; //morre
                }
            }
            //regras para celulas mortas
            else {
                if (vizinhosVivos == 3) {
                    novoReticulado->reticulado[indice].valor = 1; //nasce
                } else {
                    novoReticulado->reticulado[indice].valor = 0; //morta
                }
            }
            novoReticulado -> reticulado[indice].x = i;
            novoReticulado -> reticulado[indice].y = j;
        }
    }

    //substitui o reticulado atual
    desalocarReticulado(*reticulado); // Desaloca a memória do reticulado original
    *reticulado = novoReticulado;//copia os novos valores para o antigo*/
}



















