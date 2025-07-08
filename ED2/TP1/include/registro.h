#ifndef REGISTRO_H
#define REGISTRO_H

#define TAM_DADO2 1000
#define TAM_DADO3 5000
#define REG_POR_PAGINA 8  // Definido como padrão único para MS e MP

typedef struct {
    int chave;          // chave de pesquisa
    long dado1;         // valor inteiro longo
    char dado2[TAM_DADO2];  // cadeia de caracteres
    char dado3[TAM_DADO3];  // cadeia de caracteres
} Registro; // estrutura de registro 

#endif

