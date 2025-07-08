#include "maquina.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void criarMemoriaExterna(){
    for(int i = 0; i < 1000; i++){
        char nomeArquivo[20];
        sprintf(nomeArquivo, "%d.txt", i);//gera o nome dos arquivos baseados em blocos de memoria
        FILE *arquivo = fopen(nomeArquivo, "w");
        if(arquivo == NULL){
            printf("Erro ao criar o arquivo %s\n", nomeArquivo);//verificacao para caso o arquivo nao for salvo corretamente
            continue;
        }
        for(int j = 0; j < 4; j++){
            int valor = rand() % 4;//gera valores de 0 a 3
            fprintf(arquivo, "%d\n", valor);
        }
        fclose(arquivo);//fecha o arquivo
    }
}

void inicializarRam(memoriaRam *ram) {
    for (int i = 0; i < TAMANHO_RAM; i++) {
        for (int j = 0; j < PALAVRAS_POR_BLOCO; j++) {
            ram->blocos[i].palavras[j] = 0; //preenche com 0 pois esta inicialmente vazia
        }
        ram->blocos[i].valido = 0; //valida como 0 pois inicialmente esta vazia
        ram->blocos[i].tag = -1; //usaremos -1 para demonstrar que nao ha nenhum bloco aqui
    }
}

void inicializarCaches(cacheL1 *l1, cacheL2 *l2, cacheL3 *l3) {
    for (int i = 0; i < TAMANHO_L1; i++) {
        l1->blocos[i].valido = 0;//valida como 0 pois inicialmente esta vazia
        l1->blocos[i].tag = -1;//usamos -1 pra demonstrar que nao ha nenhum bloco aqui
        l1->blocos[i].contadorLRU = 0;//id de entrada do elemento
        for (int j = 0; j < PALAVRAS_POR_BLOCO; j++) {
            l1->blocos[i].palavras[j] = 0;
        }
    }

    l1->acessos = 0;
    l1->hits = 0;
    l1->misses = 0;
    l1->contadorGlobalLRU = 0;//contador pra controlar as entradas na cache

    for (int i = 0; i < TAMANHO_L2; i++) {
        l2->blocos[i].valido = 0;//valida como 0 pois inicialmente esta vazia
        l2->blocos[i].tag = -1;//usamos -1 pra demonstrar que nao ha nenhum bloco aqui
        l2->blocos[i].contadorLRU = 0;//id de entrada do elemento
        for (int j = 0; j < PALAVRAS_POR_BLOCO; j++) {
            l2->blocos[i].palavras[j] = 0;
        }
    }
    l2->acessos = 0;
    l2->hits = 0;
    l2->misses = 0;
    l2->contadorGlobalLRU = 0;//contador pra controlar as entradas na cache

    for (int i = 0; i < TAMANHO_L3; i++) {
        l3->blocos[i].valido = 0;//valida como 0 pois inicialmente esta vazia
        l3->blocos[i].tag = -1;//usamos -1 pra demonstrar que nao ha nenhum bloco aqui
        l3->blocos[i].contadorLRU = 0;//id de entrada do elemento
        for (int j = 0; j < PALAVRAS_POR_BLOCO; j++) {
            l3->blocos[i].palavras[j] = 0;
        }
    }
    l3->acessos = 0;
    l3->hits = 0;
    l3->misses = 0;
    l3->contadorGlobalLRU = 0;//contador pra controlar as entradas na cache
}

void imprimirRam(const memoriaRam *ram) {
    for (int i = 0; i < TAMANHO_RAM; i++) {
        printf("bloco %d: ", i);
        for (int j = 0; j < PALAVRAS_POR_BLOCO; j++) {
            printf("%d ", ram->blocos[i].palavras[j]);
        }
        printf("\n");
    }
}

void processarInstrucoes(const char* filename, const char* filename2, int num_instrucoes, cacheL1 *l1, cacheL2 *l2, cacheL3 *l3, memoriaRam *ram) {

    //abertura do arquivo

    FILE* arquivo = fopen(filename, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de instrucoes.\n");
        return;
    }

    //abertura do arquivo de interrupcoes para simular a interrupcao
    FILE* arquivo2 = fopen(filename2, "r");
    if (!arquivo2) {
        printf("Erro ao abrir o arquivo de interrupcoes.\n");
        return;
    }

    //contexto para salvar a execucao da maquina

    Contexto contextoAtual;//cria uma variavel auxiliar para sempre salvar os dados caso haja uma interrupcao
    int contadorPrograma = 0;

    //inicia a maquina

    for (int i = 0; i < num_instrucoes; i++) {

        printf("Executando instrucao: %d\n", contadorPrograma);//comeca a execucao das instrucoes

        if(checarInterrupcao()){
            salvarContexto(&contextoAtual, contadorPrograma, l1, l2, l3, ram);//salva o estado da maquina antes da interrupcao
            tratarInterrupcao(arquivo2, l1, l2, l3, ram);//trata a interrupcao
            restaurarContexto(&contextoAtual, &contadorPrograma, l1, l2, l3, ram);//restaura o contexto para continuar a execucao da maquina
        }

        int opcode, bloco1, palavra1, bloco2, palavra2, bloco_res, palavra_res;//inicializa as variaveis auxiliares para realizar as operacoes
        fscanf(arquivo, "%d:%d:%d:%d:%d:%d:%d\n", &opcode, &bloco1, &palavra1, &bloco2, &palavra2, &bloco_res, &palavra_res);//pega os valores das instrucoes para execucao

        printf("Instrução %d: opcode: %d, bloco1: %d palavra1: %d, bloco2: %d palavra2: %d, bloco Res: %d palavra res: %d\n", i, opcode, bloco1, palavra1, bloco2, palavra2, bloco_res, palavra_res); //mostra qual instrucao esta sendo realizada pela maquina

        //busca os valores desejados na memoria para realizar a operacao

        int valor1 = buscarNaCacheEOperar(bloco1, palavra1, opcode, l1, l2, l3, ram); //busca os valores desejados 
        int valor2 = buscarNaCacheEOperar(bloco2, palavra2, opcode, l1, l2, l3, ram); //busca os valores desejados

        int resultado; //inicializa a variavel para armazenar o resultado da operacao
        if (opcode == 0) { 
            resultado = valor1 + valor2;//soma os valores desejados para realizar a operacao
        } else if (opcode == 1) { //subtracao
            resultado = valor1 - valor2;//subtrai os valores desejados para a operacao
        }

        ram->blocos[bloco_res].palavras[palavra_res] = resultado;//armazena o valor da operacao no endereco desejado na memoria

        printf("Resultado: %d\n", resultado); //mostra o resultado da operacao

        contadorPrograma++;//atualiza o contador do numero de instrucoes
    }

    //fecha o processamento

    fclose(arquivo);
    fclose(arquivo2);
}

int buscarNaCacheEOperar(int enderecoBloco, int palavra, int opcode, cacheL1 *l1, cacheL2 *l2, cacheL3 *l3, memoriaRam *ram) {

    //buscar na cache 1

    for (int i = 0; i < TAMANHO_L1; i++) {
        if (l1->blocos[i].valido && l1->blocos[i].tag == enderecoBloco) {
            l1->acessos++; //contabilizar acesso
            l1->hits++; //contabilizar hit caso aconteca
            l1->blocos[i].contadorLRU = l1->contadorGlobalLRU++; //atualiza o contador do elemento pois ele foi usado recentemente
            return l1->blocos[i].palavras[palavra]; //retorna o valor desejado pra operacao
        }
    }

    //busca na cache 2

    for (int i = 0; i < TAMANHO_L2; i++) {
        if (l2->blocos[i].valido && l2->blocos[i].tag == enderecoBloco) {
            l2->acessos++; //contabiliza o acesso a cache 2
            l2->hits++; //contabiliza o hit a cache 2
            l2->blocos[i].contadorLRU = l2->contadorGlobalLRU++;//atualiza o contador do elemento pois ele foi usado recentemente
            carregarParaCache(l1->blocos, TAMANHO_L1, enderecoBloco, l2->blocos[i].palavras, &l1->contadorGlobalLRU);//leva ele pra cache 1
            return l2->blocos[i].palavras[palavra];
        }
    }

    for (int i = 0; i < TAMANHO_L3; i++) {
        if (l3->blocos[i].valido && l3->blocos[i].tag == enderecoBloco) {
            l3->acessos++;//contabiliza o acesso a cache 3
            l3->hits++;//contabiliza o hit na cache 3
            l3->blocos[i].contadorLRU = l3->contadorGlobalLRU++;//atualiza o contador do elemento pois ele foi usado recentemente
            carregarParaCache(l2->blocos, TAMANHO_L2, enderecoBloco, l3->blocos[i].palavras, &l2->contadorGlobalLRU);//carrega pra cache 2
            carregarParaCache(l1->blocos, TAMANHO_L1, enderecoBloco, l3->blocos[i].palavras, &l1->contadorGlobalLRU);//carrega pra cache 1
            return l3->blocos[i].palavras[palavra];
        }
    }

    //caso nao esteja em nenhuma cache e nem na ram carregar da memoria externa para a ram
    if(!ram -> blocos[enderecoBloco].valido){
        char nomeArquivo[20];//variavel para buscar o arquivo na memoria externa
        sprintf(nomeArquivo, "%d.txt", enderecoBloco);//preenchemos a variavel com o nome do arquivo que contem o bloco desejado
        carregarDadosNaRam(ram, nomeArquivo, enderecoBloco);//buscamos o arquivo que contem o bloco desejado e carregamos na ram
        ram -> misses++;//como o dado nao foi achado na ram buscamos na memoria externa
    }

    //com o bloco ja na ram retornamos o valor desejado
    int valor = ram->blocos[enderecoBloco].palavras[palavra];

    //copia o bloco pra l3
    carregarParaCache(l3->blocos, TAMANHO_L3, enderecoBloco, ram->blocos[enderecoBloco].palavras, &l3->contadorGlobalLRU);
    //copia o bloco pra l2
    carregarParaCache(l2->blocos, TAMANHO_L2, enderecoBloco, ram->blocos[enderecoBloco].palavras, &l2->contadorGlobalLRU);
    //copia o bloco pra l1
    carregarParaCache(l1->blocos, TAMANHO_L1, enderecoBloco, ram->blocos[enderecoBloco].palavras, &l1->contadorGlobalLRU);

    //contabiliza as percas visto que nenhum valor foi acessado nas caches

    l1->misses++;
    l2->misses++;
    l3->misses++;

    return valor;
}

void carregarParaCache(blocoMemoria *cache, int tamanhoCache, int enderecoBloco, int palavras[PALAVRAS_POR_BLOCO], int *contadorGlobalLRU) {
    //variaveis auxiliares para ajudar na busca do elemento mais antigo
    int menorLRU = *contadorGlobalLRU;
    int indiceSubstituicao = 0;

    for (int i = 0; i < tamanhoCache; i++) {
        if (cache[i].valido == 0) {

            //caso haja um espaco valido na memoria nao substituir

            indiceSubstituicao = i;
            break;
        }

        //caso a cache estiver cheia pegar o indice do elemento mais antigo e substituir

        if (cache[i].contadorLRU < menorLRU) {
            menorLRU = cache[i].contadorLRU;
            indiceSubstituicao = i;
        }
    }

    //substitui o bloco na cache
    cache[indiceSubstituicao].valido = 1;
    cache[indiceSubstituicao].tag = enderecoBloco;
    cache[indiceSubstituicao].contadorLRU = *contadorGlobalLRU;
    (*contadorGlobalLRU)++;
    memcpy(cache[indiceSubstituicao].palavras, palavras, sizeof(int) * PALAVRAS_POR_BLOCO);//copia os valores para o novo bloco
}

void carregarDadosNaRam(memoriaRam *ram, const char *nomeArquivo, int enderecoBloco){
    //verifica se o endereco buscado existe na memoria externa
    if(enderecoBloco < 0 || enderecoBloco >= 1000){
        fprintf(stderr, "Endereco invalido: %d\n", enderecoBloco);//informamos erro caso o endereco seja invalido
        return;//retornamos
    }
    FILE *arquivo = fopen(nomeArquivo, "r");//abrimos o arquivo correspondente ao endereco
    if(arquivo == NULL){
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", nomeArquivo);//verificamos se o arquivo foi aberto corretamente
        return;//retornamos
    }
    //le as 4 palavras correspondentes ao bloco
    for(int i = 0; i < 4; i++){
        if(fscanf(arquivo, "%d", &ram -> blocos[enderecoBloco].palavras[i]) != 1){
            fprintf(stderr, "Erro ao ler os dados do arquivo: %s\n", nomeArquivo); //verificamos se os dados foram lidos corretamente
            fclose(arquivo);//fechamos o arquivo
            return;//retornamos
        }
    }
    ram -> blocos[enderecoBloco].valido = 1;//validamos o endereco da ram na qual os dados foram armazenados
    ram -> blocos[enderecoBloco].tag = enderecoBloco;//passamos a tag para o bloco correspondente da ram
    fclose(arquivo);//fechamos o arquivo
}

void salvarContexto(Contexto *contextoAtual, int contadorPrograma, cacheL1 *l1, cacheL2 *l2, cacheL3 *l3, memoriaRam *ram){
    contextoAtual->contadorPrograma = contadorPrograma;//salva o estado no qual o programa estava antes de ser interrompido
    contextoAtual->l1 = *l1;//salva o estado da cache l1
    contextoAtual->l2 = *l2;//salva o estado da cache l2
    contextoAtual->l3 = *l3;//salva o estado da cache l3
    contextoAtual->ram = *ram;//salva o estado da ram
}

void restaurarContexto(Contexto *contextoAtual, int *contadorPrograma, cacheL1 *l1, cacheL2 *l2, cacheL3 *l3, memoriaRam *ram){
    *contadorPrograma = contextoAtual -> contadorPrograma;//restaura a instrucao que estava sendo executada
    *l1 = contextoAtual -> l1;//restaura o estado da cache l1
    *l2 = contextoAtual -> l2;//restaura o estado da cache l2
    *l3 = contextoAtual -> l3;//restaura o estado da cache l3
    *ram = contextoAtual -> ram;//restaura o estado da ram
}

int checarInterrupcao(){
    int probabilidade  = rand() % 100;//gera um numero de 0 a 99
    return (probabilidade < 10);//define que uma sera ocorrida com 10% de chance
}

void tratarInterrupcao(FILE* filename, cacheL1 *l1, cacheL2 *l2, cacheL3 *l3, memoriaRam *ram){
    int opcode, bloco1, palavra1, bloco2, palavra2, bloco_res, palavra_res;//inicializa as variaveis auxiliares para realizar as operacoes
    fscanf(filename, "%d:%d:%d:%d:%d:%d:%d\n", &opcode, &bloco1, &palavra1, &bloco2, &palavra2, &bloco_res, &palavra_res);//pega os valores das instrucoes para execucao

    printf("Tratando Interrupcao: opcode: %d, bloco1: %d palavra1: %d, bloco2: %d palavra2: %d, bloco Res: %d palavra res: %d\n", opcode, bloco1, palavra1, bloco2, palavra2, bloco_res, palavra_res); //mostra qual instrucao sera feita para resolver a interrupcao

    //busca os valores desejados na memoria para realizar a operacao

    int valor1 = buscarNaCacheEOperar(bloco1, palavra1, opcode, l1, l2, l3, ram); //busca os valores desejados 
    int valor2 = buscarNaCacheEOperar(bloco2, palavra2, opcode, l1, l2, l3, ram); //busca os valores desejados

    int resultado; //inicializa a variavel para armazenar o resultado da operacao
    if (opcode == 0) { 
        resultado = valor1 + valor2;//soma os valores desejados para realizar a operacao
    } 
    else if (opcode == 1) { //subtracao
        resultado = valor1 - valor2;//subtrai os valores desejados para a operacao
    }

    ram->blocos[bloco_res].palavras[palavra_res] = resultado;//armazena o valor da operacao no endereco desejado na memoria

    printf("Resultado: %d\n", resultado); //mostra o resultado da operacao
}

