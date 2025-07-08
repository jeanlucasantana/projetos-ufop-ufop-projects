// *arquivo de cabecalho(header) com os prototipos das funcoes e estruturas

#ifndef AUTOMATO_H
#define AUTOMATO_H

//struct que armazena os dados de um reticulado.
typedef struct {
    int** reticulado;
    int tamanho;
    int geracoes;
} Reticulado;

//funcao para alocar uma matriz 2D dinamicamente

Reticulado* alocarReticulado(int tamanho, int geracoes);

//funcao para desalocar uma matriz 2D dinamicamente
void desalocarReticulado(Reticulado *reticulado);

//funcao para ler o reticulado do terminal
Reticulado* LeituraReticulado(int* tamanho, int* geracoes);

//funcao para imprimir o reticulado
void imprimeReticulado(Reticulado *reticulado);

//funcao para limpar o buffer do terminal
void limparBuffer();

//funcao para verificar se os numeros inseridos no terminal sao inteiros
bool lerInteiro(int* valor);

//funcao para contar os vizinhos vivos de determinada celula
int contarVizinhosVivos(Reticulado* reticulado, int linha, int coluna);

//funcao para determinar as proximas geracoes do reticulado e o reticulado final
void evoluirReticulado(Reticulado* reticuladoAtual, Reticulado* novoReticulado, int tamanho, int geracaoAtual, int geracoes);

#endif
