#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "automato.h"

int main(){
    int tamanho;
    int geracoes;
    Reticulado* reticulado = LeituraReticulado(&tamanho, &geracoes);
    Reticulado* novoReticulado = alocarReticulado(tamanho, geracoes);
    printf("Reticulado Inicial: \n");
    imprimeReticulado(reticulado);
    evoluirReticulado(reticulado, novoReticulado, tamanho, 0, geracoes);
    printf("Reticulado Final: \n");
    imprimeReticulado(novoReticulado);
    desalocarReticulado(reticulado);
    desalocarReticulado(novoReticulado);
    return 0;
}