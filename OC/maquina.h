#ifndef MAQUINA_H
#define MAQUINA_H
#include <stdio.h>

//definindo o tamanho das estruturas em base 2

#define PALAVRAS_POR_BLOCO 4
#define TAMANHO_L1 32
#define TAMANHO_L2 64
#define TAMANHO_L3 128
#define TAMANHO_RAM 1024
#define TAMANHO_MEMORIA_EXTERNA 4096


//estrutura de um bloco de memoria

typedef struct {
    int palavras[PALAVRAS_POR_BLOCO];
    int valido;
    int tag;
    int contadorLRU;
} blocoMemoria;

//estrutura da cache 1

typedef struct {
    blocoMemoria blocos[TAMANHO_L1];
    int acessos;
    int hits;
    int misses;
    int contadorGlobalLRU;
} cacheL1;

//estrutura da cache 2

typedef struct {
    blocoMemoria blocos[TAMANHO_L2];
    int acessos;
    int hits;
    int misses;
    int contadorGlobalLRU;
} cacheL2;

//estrutura da cache 3

typedef struct {
    blocoMemoria blocos[TAMANHO_L3];
    int acessos;
    int hits;
    int misses;
    int contadorGlobalLRU;
} cacheL3;

//estrutura da ram 

typedef struct {
    blocoMemoria blocos[TAMANHO_RAM];
    int misses; //contabilizamos apenas os misses pois usaremos a ram para carregar as copias de toda maneira
} memoriaRam;

//estrutura pra armazenar o contexto antes de uma interrupcao

typedef struct{
    int contadorPrograma; //guarda em qual instrucao o programa estava antes de ser interrompido
    cacheL1 l1;//armazena o estado atual da cache l1
    cacheL2 l2;//armazena o estado atual da cache l2
    cacheL3 l3;//armazena o estado atual da cache l3
    memoriaRam ram;//armazena o estado atual da ram
} Contexto; 

//criar memoria externa

void criarMemoriaExterna();

//inicializar ram

void inicializarRam(memoriaRam *ram);

//inicializar as caches

void inicializarCaches(cacheL1 *l1, cacheL2 *l2, cacheL3 *l3);

//imprimir a ram

void imprimirRam(const memoriaRam *ram);

//funcao que simula a maquina

void processarInstrucoes(const char* filename, const char* filename2, int num_instrucoes, cacheL1 *l1, cacheL2 *l2, cacheL3 *l3, memoriaRam *ram);

//funcao para processar os dados

int buscarNaCacheEOperar(int enderecoBloco, int palavra, int opcode, cacheL1 *l1, cacheL2 *l2, cacheL3 *l3, memoriaRam *ram);

//funcao para buscar na memoria externa

void carregarDadosNaRam(memoriaRam *ram, const char *nomeArquivo, int enderecoBloco);

//funcao auxiliar para levar as copias as memorias

void carregarParaCache(blocoMemoria *cache, int tamanhoCache, int enderecoBloco, int palavras[PALAVRAS_POR_BLOCO], int *contadorGlobalLRU);

//funcao para salvar o estado atual da maquina

void salvarContexto(Contexto *contextoAtual, int programCounter, cacheL1 *l1, cacheL2 *l2, cacheL3 *l3, memoriaRam *ram);

//funcao para retornar o contexto apos as interrupcoes

void restaurarContexto(Contexto *contextoAtual, int *contadorPrograma, cacheL1 *l1, cacheL2 *l2, cacheL3 *l3, memoriaRam *ram);

//funcao para verificar se houve uma interrupcao durante a execucao do programa

int checarInterrupcao();

//funcao para tratar a interrupcao

void tratarInterrupcao(FILE *filename, cacheL1 *l1, cacheL2 *l2, cacheL3 *l3, memoriaRam *ram);

#endif