# 🖥️ Organização de Computadores | Computer Organization

Este projeto simula o funcionamento de uma máquina com múltiplos níveis de memória cache (L1, L2 e L3), memória RAM e memória externa. Ele processa instruções a partir de um arquivo de entrada, realiza o acesso à memória simulada e apresenta estatísticas de desempenho da cache.

This project simulates the operation of a machine with multiple levels of cache memory (L1, L2, and L3), RAM, and external memory. It processes instructions from an input file, performs simulated memory access, and presents cache performance statistics.

---

## ⚙️ Fluxo Principal | Main Flow

1. O programa verifica se os parâmetros de entrada estão corretos (espera receber dois arquivos de instruções).  
2. Inicializa a semente aleatória para popular a memória externa com dados simulados.  
3. Cria a memória externa simulada.  
4. Inicializa as estruturas de cache L1, L2 e L3 e a memória RAM vazia.  
5. Solicita ao usuário o número de instruções que serão processadas.  
6. Processa as instruções conforme o arquivo de entrada e o número informado, simulando o acesso à memória e gerenciamento das caches.  
7. Após o processamento, exibe estatísticas de acesso, hits e misses para cada nível de cache, além do número de acessos à memória externa.

---

## 🗂️ Estrutura do Projeto | Project Structure

- `maquina.h` e arquivos relacionados: Definem as estruturas de dados para cache e memória, além das funções de inicialização e processamento.  
- Arquivos de entrada: Arquivos de texto contendo as instruções que serão processadas pela simulação.  
- Funções principais:
  - `criarMemoriaExterna()` — inicializa e popula a memória externa.  
  - `inicializarRam()` — inicializa a memória RAM.  
  - `inicializarCaches()` — inicializa as caches L1, L2 e L3.  
  - `processarInstrucoes()` — lê e processa as instruções, atualizando os estados das caches e memória.

---

## 📋 Como usar | How to use

```bash
./programa <arquivo_de_instrucoes.txt> <arquivo_de_saida.txt>
