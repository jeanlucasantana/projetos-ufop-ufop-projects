#include <stdio.h>
#include "arvore_b.h"
#include "inserir_arvore_b.h"

void debug_no_raiz_arvore_b(const char* caminho) {
    printf("Raiz da arvore B: \n");  // isto deveria aparecer
    FILE* arq = fopen(caminho, "rb");
    if (!arq) {
        printf("Erro ao abrir o arquivo: %s\n", caminho);
        return;
    }

    NoB no;
    ler_no_indexado(arq, &no, 0);  // raiz no índice 0

    printf("Número de chaves na raiz: %d\n", no.num_chaves);
    printf("Chaves: \n");
    for (int i = 0; i < no.num_chaves; i++) {
        printf("%d ", no.chaves[i]);
    }
    printf("\n");

    fclose(arq);
}
