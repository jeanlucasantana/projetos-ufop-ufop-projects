#include "automato.h"
#include "matriz.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void evoluirReticulado(listaLinhas* linhas, listaColunas* colunas, listaLinhas* novasLinhas, listaColunas* novasColunas, int tam) {
    // inicializa as novas listas
    alocarReticulado(novasLinhas, novasColunas); // setar as novas listas como nulas

    // percorrer todas as celulas vivas atuais
    nCelula* celula = linhas->primeiraLinha;

    while (celula != NULL) {
        int linha = celula->celula.linha;
        int coluna = celula->celula.coluna;

        // variavel auxiliar para contar o numero de vizinhos vivos de cada celula
        int vizinhosVivos = 0;

        for (int i = linha - 1; i <= linha + 1; i++) {
            for (int j = coluna - 1; j <= coluna + 1; j++) {
                if (i == linha && j == coluna) continue; // ignorar a propria celula

                // checar se as celulas vizinhas estao vivas
                nCelula* checarLinha = linhas->primeiraLinha;
                while (checarLinha != NULL) {
                    if (checarLinha->celula.linha == i && checarLinha->celula.coluna == j) {
                        vizinhosVivos++;
                        break;
                    }
                    checarLinha = checarLinha->proximaLinha;
                }
            }
        }

        // aplicar as regras do automato de conway
        if (vizinhosVivos == 2 || vizinhosVivos == 3) {
            // criar uma nova celula com as mesmas coordenadas
            nCelula* novaCelula = malloc(sizeof(nCelula));
            novaCelula->celula.linha = linha;
            novaCelula->celula.coluna = coluna;
            novaCelula->proximaLinha = NULL;
            novaCelula->proximaColuna = NULL;

            // adicionar as novas listas
            adicionarCelulaLinha(novasLinhas, novaCelula);
            adicionarCelulaColuna(novasColunas, novaCelula);
        }

        // passa para a proxima celula a ser analisada
        celula = celula->proximaLinha;
    }

    // agora, verificar as celulas mortas (posiçao onde nao existe celula viva)
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            int vizinhosVivos = 0;

            for (int x = i - 1; x <= i + 1; x++) {
                for (int y = j - 1; y <= j + 1; y++) {
                    if (x == i && y == j) continue;

                    nCelula* checarLinha = linhas->primeiraLinha;
                    while (checarLinha != NULL) {
                        if (checarLinha->celula.linha == x && checarLinha->celula.coluna == y) {
                            vizinhosVivos++;
                            break;
                        }
                        checarLinha = checarLinha->proximaLinha;
                    }
                }
            }

            if (vizinhosVivos == 3) {
                // adicionar nova celula viva
                nCelula* novaCelula = malloc(sizeof(nCelula));
                novaCelula->celula.linha = i;
                novaCelula->celula.coluna = j;
                novaCelula->proximaLinha = NULL;
                novaCelula->proximaColuna = NULL;

                adicionarCelulaLinha(novasLinhas, novaCelula);
                adicionarCelulaColuna(novasColunas, novaCelula);
            }
        }
    }

    // desalocar o reticulado antigo
    desalocarReticulado(linhas);

    // copiar o conteudo das novas listas para as listas atuais
    *linhas = *novasLinhas;
    *colunas = *novasColunas;

    // limpar as novas listas
    novasLinhas->primeiraLinha = NULL;
    novasColunas->primeiraColuna = NULL;
}
