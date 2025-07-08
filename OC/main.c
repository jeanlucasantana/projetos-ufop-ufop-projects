#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "maquina.h"

int main(int argc, char *argv[]) {
    //verifica se o numero de arquivos esta correto
    if (argc != 3) {
        printf("Uso: %s <arquivo_de_instrucoes.txt>\n", argv[0]);
        return 1;
    }

    //inicializa a semente para preencher os valores da memoria externa
    srand(time(NULL));
    criarMemoriaExterna();//cria a memoria externa

    //inicializa as variaveis
    cacheL1 l1;//variavel que representa a cache l1
    cacheL2 l2;//variavel que representa a cache l2
    cacheL3 l3;//variavel que representa a cache l3
    memoriaRam ram;//variavel que representa a memoria ram
    int aux;//variavel que armazena o numero de instrucoes que serao processadas

    //inicializa as estruturas 
    inicializarRam(&ram);//inicializa a ram vazia
    inicializarCaches(&l1, &l2, &l3);//inicializa as caches vazias
    printf("Digite o numero de instrucoes a serem recebidas:\n");//recebe o numero de instrucoes que serao processadas
    scanf("%d", &aux);//armazena o numero de instrucoes a serem processadas

    //processa a quantidade de instrucoes solicitadas
    processarInstrucoes(argv[1], argv[2                                                                                                                                                                                                                                                                                                                                                                                                                                     ], aux, &l1, &l2, &l3, &ram);

    //exibe os resultados da cache 
    printf("Cache L1 - Acessos: %d, Hits: %d, Misses: %d\n", l1.acessos, l1.hits, l1.misses);
    printf("Cache L2 - Acessos: %d, Hits: %d, Misses: %d\n", l2.acessos, l2.hits, l2.misses);
    printf("Cache L3 - Acessos: %d, Hits: %d, Misses: %d\n", l3.acessos, l3.hits, l3.misses);
    printf("Memoria Externa - Acessos: %d\n", ram.misses);
    return 0;
}