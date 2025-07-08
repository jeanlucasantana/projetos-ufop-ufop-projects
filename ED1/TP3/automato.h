//arquivo de cabecalho(header) com os prototipos das funcoes e estruturas

#ifndef AUTOMATO_H
#define AUTOMATO_H

//estrutura que representa a celula

typedef struct{
    int x;
    int y;
    int valor;
}Celula;

//estrutura que representa o reticulado

typedef struct{
    Celula *reticulado;
    int linhas;
    int colunas;
    int tamanhoTotal;
    int geracoes;
}Reticulado;

//funcao para alocar memoria para um reticulado

Reticulado* alocarReticulado(int tamanho, int geracoes);

//funcao para desalocar memoria de uma estrutura reticulado

void desalocarReticulado(Reticulado* reticulado);

//funcoes para leitura dos valores do reticulado no terminal

void limparBuffer();
bool lerInteiro(int* valor);
Reticulado* leituraReticulado(int* tamanho, int* geracoes);

//funcao para imprimir o reticulado
void imprimeReticulado(Reticulado* reticulado);

//funcoes para evolucao do reticulado
int contarVizinhosVivos(Reticulado* reticulado, int i, int j);
void evoluirReticulado(Reticulado** reticulado);







































#endif
