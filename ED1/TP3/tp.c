#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "automato.h"
#include "double_hash.h"

int main(){
    int tamanho;//variavel para receber o tamanho do reticulado
    int geracoes;//variavel para receber o numero de geracoes a serem geradas
    Reticulado* reticulado = leituraReticulado(&tamanho, &geracoes);//leitura dos dados necessarios
    // verifica o numero de geracoes
    if (geracoes == 0) {
        //printf("Reticulado Inicial:\n");
        imprimeReticulado(reticulado);
        desalocarReticulado(reticulado);
        return 1; 
    }
    //printf("Reticulado Inicial: \n");//mensagem para impressao do reticulado
    //imprimeReticulado(reticulado);//imprime o reticulado inicial
    for(int g = 0; g < geracoes; g++){
        //printf("Evoluindo celula");
        evoluirReticulado(&reticulado);//evolui o reticulado
    }
    //printf("Reticulado Final: \n");//mensagem para impressao do reticulado
    imprimeReticulado(reticulado);//imprime o reticulado
    desalocarReticulado(reticulado);//desaloca o reticulado
    return 0;
}