#ifndef SISTEMA_H
#define SISTEMA_H

#include "Aeronave.hpp"
#include "Pessoa.hpp"
#include "Voos.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;


class Sistema {
private:
    vector<Aeronave*> aeronaves;
    vector<Passageiro*> passageiros;
    vector<Piloto*> pilotos;
    vector<Voos*> voos;

public:
    // Menu principal do sistema
    void menuPrincipal();

    // Funcionalidades principais
    void cadastrarAeronave();
    void cadastrarPessoa();
    void criarVoo();
    void associarPassageiro();
    void listarVoos();
    void listarPassageirosVoo();
    void salvarDados();
    void carregarDados();
    void gerarRelatorios(); // ponto extra mano
    void adicionarAeronave(const string& codigo, const string& modelo, int capacidade, double velocidade, double autonomia);
    void adicionarPiloto(const string& nome, const string& matricula, const string& breve, int horas);
    void adicionarPassageiro(const string& nome, const string& cpf, const string& bilhete);
    vector<std::string> obterResumoVoos() const;
    string listarPassageirosDeVoo(const string& codigoVoo) const;
    string gerarRelatorioTexto() const;
    void adicionarVoo(Voos* v); 
};

#endif
