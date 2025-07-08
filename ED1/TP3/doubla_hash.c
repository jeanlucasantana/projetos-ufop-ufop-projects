#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "double_hash.h"
#include "automato.h"

int hash1(int x, int y, int tamanho){
    int pesos[2] = {1, 2};//vetor de pesos para alterar as chaves
    return (pesos[0] * x + pesos[1] * y) % tamanho;//calculo do indice
}

int hash2(int x, int y, int tamanho){
    int pesos[2] = {3, 4};//vetor de pesos para alterar as chaves
    return (pesos[0] * x + pesos[1] * y) % tamanho;//calculo do indice
}

void inserirHash(Reticulado* reticulado, int i, int j, int valor){
    Celula novaCelula; //variavel temporaria para receber as celulas
    novaCelula.x = i;//coordenada x
    novaCelula.y = j;//coordenada y
    novaCelula.valor = valor;//valor da celula(0 ou 1)
    int indice = hash1(i, j, reticulado -> tamanhoTotal);//aplicando a primeira funcao hash
    //verificacao para colisoes
    if(reticulado -> reticulado[indice].valor != -1){
        int indice2 = hash2(i, j, reticulado -> tamanhoTotal);//aplica uma segunda funcao hash
        int novoIndice = (indice + indice2) % reticulado -> tamanhoTotal;//calcula o novo indice
        while(reticulado -> reticulado[novoIndice].valor != -1){
            novoIndice = (novoIndice + indice2) % reticulado -> tamanhoTotal;//enquanto houver colisoes um novo indice sera calculado
        }
        indice = novoIndice;//novo indice foi determinado para o elemento
    }
    reticulado -> reticulado[indice] = novaCelula;//armazenamos o elemento
    //printf("Inserido: (%d, %d) -> valor: %d no indice %d\n", i, j, valor, indice);
}

int pesquisarCelula(Reticulado* reticulado, int x, int y){
    int indice = hash1(x, y, reticulado -> tamanhoTotal);//aplica a primeira funcao hash
    //verifica se a celula encontrada esta correta
    if(reticulado -> reticulado[indice].x == x && reticulado -> reticulado[indice].y == y){
        return indice;//encontrou a celula
    }
    //aplica a hash2(colisao)
    int indice2 = hash2(x, y, reticulado -> tamanhoTotal);//aplica a hash2
    int novoIndice = (indice + indice2) % reticulado -> tamanhoTotal;//calcula o novo indice
    //procura a celula com as coordenadas corretas
    while(reticulado -> reticulado[novoIndice].x != -1){
        if(reticulado -> reticulado[novoIndice].x == x && reticulado -> reticulado[novoIndice].y == y){
            return novoIndice;//achou o elemento
        }
        novoIndice = (novoIndice + indice2) % reticulado -> tamanhoTotal;//recalcula o indice ate achar o elemento desejado
    }
    return -1;//celula nao encontrada
}









