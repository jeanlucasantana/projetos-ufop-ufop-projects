#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "registro.h"
#include "sequencial_indexado_ms.h"
#include "arvore_b.h"
#include "inserir_arvore_b.h"
#include "arvore_binaria.h"
#include "arvoreb_estrela.h"
#include "debug.h"

// variaveis globais para metricas
int transferencias = 0;
int comparacoes = 0;
clock_t inicio_exec;

void iniciar_contagem() {
    transferencias = 0;
    comparacoes = 0;
    inicio_exec = clock();
} //funcao para iniciar as metricas

void exibir_metricas() {
    double tempo = (double)(clock() - inicio_exec) / CLOCKS_PER_SEC;
    printf("Transferências: %d\n", transferencias);
    printf("Comparações: %d\n", comparacoes);
    printf("Tempo: %.6f s\n", tempo);
} //funcao para visualizar as metricas apos a busca

void exibir_registro(Registro* r) {
    if (r) {
        printf("Chave: %d\n", r->chave);
        printf("Dado1: %ld\n", r->dado1);
        printf("Dado2: %.10s...\n", r->dado2);
        printf("Dado3: %.10s...\n", r->dado3);
    } else {
        printf("Registro não encontrado\n");
    }
} //funcao para visualizar o registro buscado

// funcao principal que faz a busca nos arquivos e exibe os resultados das metricas 
int main(int argc, char* argv[]) {
    if (argc < 5) {
        printf("Uso: %s <método> <quantidade> <situação> <chave> [-P]\n", argv[0]);
        return 1;
    }

    int metodo = atoi(argv[1]);
    int quantidade = atoi(argv[2]);
    int situacao = atoi(argv[3]);
    int chave = atoi(argv[4]);
    int exibir_chaves = (argc > 5 && strcmp(argv[5], "-P") == 0);

    // preparar ambiente
    char nome_arquivo[100];
    const char* ordem_extenso;
    switch (situacao) {
    case 1: ordem_extenso = "asc"; break;
    case 2: ordem_extenso = "desc"; break;
    case 3: ordem_extenso = "rand"; break;
    default:
        printf("Situacao invalida. Use 1 (asc), 2 (desc), ou 3 (rand).\n");
        return 1;
    }
    sprintf(nome_arquivo, "data/registros_%d_%s.bin", quantidade, ordem_extenso);
    FILE* arq = fopen(nome_arquivo, "rb");
    if (!arq) {
        printf("Arquivo de dados nao encontrado: %s\n", nome_arquivo);
        return 1;
    }
    
    //inicializa metricas e variavel para armazenar informacao buscada
    iniciar_contagem();
    Registro* resultado = NULL;

    switch (metodo) {
        case 1: { // acesso sequencial indexado em memoria secundaria
            if (!arquivo_ordenado_ms(arq)) {
                printf("arquivo nao esta ordenado. Acesso sequencial indexado requer arquivo ordenado.\n");
                break;
            }// verifica se o arquivo esta ordenado(si precisa de estar ordenado)
            int total_paginas;// variavel para armazenar o total de paginas 
            IndicePagina* indice = criar_indice_ms(arq, quantidade, &total_paginas, &transferencias, &comparacoes); //cria sequencial indexado
            if (!indice) {
                printf("erro ao criar indice para acesso sequencial indexado.\n");
                break;
            }
            resultado = pesquisar_indexado_ms(arq, indice, total_paginas, chave, &transferencias, &comparacoes);
            liberar_indice_ms(indice);
            break;
        }
        case 2: { // arvore binaria
            Registro resultado;
            bool print = false; // ou true se quiser imprimir as chaves
            bool encontrado = ArvoreBinaria(arq, quantidade, chave, print, &resultado, &transferencias, &comparacoes);
            printf("Trabalho Pratico 1 - Estruturas de Dados 2 - UFOP\n");
            if (encontrado) {
                printf("--- RESULTADO ---\n");
                printf("Chave: %d\n", resultado.chave);
                printf("Dado1: %ld\n", resultado.dado1);
                printf("Dado2: %.10s...\n", resultado.dado2);
                printf("Dado3: %.10s...\n", resultado.dado3);
                printf("\n--- MÉTRICAS ---\n");
                exibir_metricas();
                fclose(arq);
                exit(0);
            } else {
                printf("Registro com chave %d nao encontrado.\n", chave);
                printf("\n--- MÉTRICAS ---\n");
                exibir_metricas();
                fclose(arq);
                exit(0);
            }
            break;
        }
        case 3: { // arvore b
            //criar arvore b
            char nome_arvore[100];
            sprintf(nome_arvore, "data/arvore_b_%d_%s.idx", quantidade, ordem_extenso);
            FILE* arq_arvore = fopen(nome_arvore, "wb+");
            if (!arq_arvore) {
            printf("Erro ao criar arquivo da arvore B.\n");
                break;
            }
            NoB* raiz = criar_no_b(1);  // raiz da arvore B
            int raiz_ind = alocar_novo_no(arq_arvore, raiz); //indice da raiz
            free(raiz);
            Registro reg; //variavel ler registros e pegar informacoes necessarias para a arvore
            long pos = 0; //variavel para posicao no arquivo

            // Insere todos os registros na árvore B, com suas posições no arquivo de dados
            for (int i = 0; i < quantidade; i++) {
                fread(&reg, sizeof(Registro), 1, arq);
                inserir_arvore_b(arq_arvore, &raiz_ind, reg.chave, pos);
                pos += sizeof(Registro);
            }

            rewind(arq); //volta o ponteiro para o inicio para ser possivel ir para a posicao da informacao desejada

            //pesquisa usando a arvore b no arquivo indice
            resultado = pesquisar_arvore_b(arq_arvore, arq, raiz_ind, chave, &transferencias, &comparacoes);
            fclose(arq_arvore);
            char caminho_debug[100];
            sprintf(caminho_debug, "data/arvore_b_%d_%s.idx", quantidade, ordem_extenso);
            debug_no_raiz_arvore_b(caminho_debug);
            break;
        }
        
        case 4: {// arvore B* 
            Registro resultado;
            bool encontrado = executar_arvore_b_estrela(arq, quantidade, chave, false, &resultado, &transferencias, &comparacoes);
            fclose(arq);
            printf("Trabalho Pratico 1 - Estruturas de Dados 2 - UFOP\n");
            if (encontrado) {
                printf("\nChave %d encontrada!\n", chave);
                printf("Dado1: %ld\n", resultado.dado1);
                printf("Dado2: %.10s\n", resultado.dado2);
                printf("Dado3: %.10s\n", resultado.dado3);
            } else {
                printf("\nchave %d nao encontrada.\n", chave);
            }
            printf("\n--- MÉTRICAS ---\n");
            exibir_metricas();
            exit(0);
        }
        default:
            printf("Método inválido\n");
    }

    // Resultados
    printf("\nTrabalho Pratico 1 - Estruturas de Dados 2 - UFOP\n");
    printf("\n--- RESULTADO ---\n");
    exibir_registro(resultado);
    printf("\n--- MÉTRICAS ---\n");
    exibir_metricas();

    //Caso quiser conferir se a busca pegou a informacao correta
    if (exibir_chaves) {
        printf("\n--- CHAVES ---\n");
        rewind(arq);
        Registro r;
        for (int i = 0; i < quantidade; i++) {
            fread(&r, sizeof(Registro), 1, arq);
            printf("%d ", r.chave);
        }
        printf("\n");
    }
    fclose(arq);
    free(resultado);
    return 0;
}
