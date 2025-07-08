#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../include/registro.h"

// funcao para gerar strings aleatorias para preencher os dados dos registros 
void gerar_string_aleatoria(char *str, int tamanho) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < tamanho - 1; i++) {
        str[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    str[tamanho - 1] = '\0';
}

// funcao de comparacao para qsort (crescente)
int cmp_asc(const void *a, const void *b) {
    return ((Registro *)a)->chave - ((Registro *)b)->chave;
}

// decrescente
int cmp_desc(const void *a, const void *b) {
    return ((Registro *)b)->chave - ((Registro *)a)->chave;
}

//main para gerar arquivos de determinado tamanho com determinada ordenacao 

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <quantidade> <ordem>\n", argv[0]);
        printf("ordem: 1 = crescente | 2 = decrescente | 3 = aleatória\n");
        return 1;
    } //verificacao dos argumentos(quantidade e ordemm)

    int quantidade = atoi(argv[1]);
    int ordem = atoi(argv[2]);

    if (quantidade <= 0 || ordem < 1 || ordem > 3) {
        printf("Parâmetros inválidos.\n");
        return 1;
    } //verifica parametros para geracao do arquivo

    Registro *registros = malloc(sizeof(Registro) * quantidade);
    if (!registros) {
        perror("Erro ao alocar memória");
        return 1;
    } //verifica se a memoria para gerar as informacoes foi alocada

    srand(time(NULL));

    for (int i = 0; i < quantidade; i++) {
        registros[i].chave = i + 1;
        registros[i].dado1 = rand();
        gerar_string_aleatoria(registros[i].dado2, TAM_DADO2);
        gerar_string_aleatoria(registros[i].dado3, TAM_DADO3);
    } //gera os dados de cada informacao 

    // ordena conforme especificado
    if (ordem == 1) {
        qsort(registros, quantidade, sizeof(Registro), cmp_asc);
    } else if (ordem == 2) {
        qsort(registros, quantidade, sizeof(Registro), cmp_desc);
    } else {
        // aleatorio: embaralha os registros
        for (int i = quantidade - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            Registro temp = registros[i];
            registros[i] = registros[j];
            registros[j] = temp;
        }
    }

    // define nome do arquivo
    char *tipo_ordem[] = {"", "asc", "desc", "rand"};
    char nome_arquivo[100];

    //pega informacoes do nome do arquivo 

    snprintf(nome_arquivo, sizeof(nome_arquivo), "data/registros_%d_%s.bin", quantidade, tipo_ordem[ordem]);

    FILE *fp = fopen(nome_arquivo, "wb");
    if (!fp) {
        perror("Erro ao criar o arquivo");
        free(registros);
        return 1;
    } //verificacao de erro para criacao do arquivo

    fwrite(registros, sizeof(Registro), quantidade, fp); //salva as informacoes no arquivo 
    fclose(fp); //fecha o arquivo 

    printf("Arquivo \"%s\" gerado com sucesso.\n", nome_arquivo);
    free(registros); //libera  a memoria usada para processas as informacoes 
    return 0;
}