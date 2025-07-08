#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "automato.h"

#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "automato.h"

int main() {
    int tam;
    int geracoes;

    // inicializar as listas 
    listaLinhas linhas;
    listaColunas colunas;
    alocarReticulado(&linhas, &colunas);

    listaLinhas novasLinhas;
    listaColunas novasColunas;
    alocarReticulado(&novasLinhas, &novasColunas);

    // ler o reticulado inicial, tamanho e numero de geracoes
    leituraReticulado(&linhas, &colunas, &geracoes, &tam);

    // verifica o numero de geracoes
    if (geracoes == 0) {
        printf("Reticulado Inicial:\n");
        imprimeReticulado(&linhas, tam);
        desalocarReticulado(&linhas);
        desalocarReticulado(&novasLinhas);
        return 1; 
    }

    printf("Reticulado Inicial:\n");
    imprimeReticulado(&linhas, tam);

    // loop para evolucao
    for (int geracao = 0; geracao < geracoes; geracao++) {
        evoluirReticulado(&linhas, &colunas, &novasLinhas, &novasColunas, tam);

        // reinicializa novasLinhas e novasColunas para a proxima iteracao
        alocarReticulado(&novasLinhas, &novasColunas);
    }

    // imprime o reticulado final apos as geracoes
    printf("Reticulado Final:\n");
    imprimeReticulado(&linhas, tam);

    // desaloca o reticulado final
    desalocarReticulado(&linhas);
    desalocarReticulado(&novasLinhas);
    

    return 0;
}
