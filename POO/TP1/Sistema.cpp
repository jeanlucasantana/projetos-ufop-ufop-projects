// Sistema.cpp
#include "Sistema.hpp"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

void Sistema::menuPrincipal() {
    int opcao;
    do {
        cout << "\n--- MENU SISTEMA DE VOOS ---\n";
        cout << "1. Cadastrar Aeronave\n";
        cout << "2. Cadastrar Pessoa\n";
        cout << "3. Criar Voo\n";
        cout << "4. Associar Passageiro a Voo\n";
        cout << "5. Listar Voos\n";
        cout << "6. Listar Passageiros de um Voo\n";
        cout << "7. Gerar Relatórios\n";
        cout << "8. Salvar Dados\n";
        cout << "9. Carregar Dados\n";
        cout << "0. Sair\nEscolha: ";

        cin >> opcao;

         if (cin.fail()) {
            cin.clear(); // limpa erro
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignora entrada inválida
            cout << "Entrada inválida. Por favor, digite um número.\n";
            continue; // volta pro início do loop
        }

        switch (opcao) {
            case 1: cadastrarAeronave(); break;
            case 2: cadastrarPessoa(); break;
            case 3: criarVoo(); break;
            case 4: associarPassageiro(); break;
            case 5: listarVoos(); break;
            case 6: listarPassageirosVoo(); break;
            case 7: gerarRelatorios(); break;
            case 8: salvarDados(); break;
            case 9: carregarDados(); break;
            case 0: cout << "Encerrando...\n"; break;
            default: cout << "Opção inválida!\n";
        }
    } while (opcao != 0);
}

void Sistema::cadastrarAeronave() {
    string codigo, modelo;
    int capacidade;
    double velocidade, autonomia;

    cout << "Código: "; cin >> codigo;
    cout << "Modelo: "; cin >> modelo;
    cout << "Capacidade: "; cin >> capacidade;
    cout << "Velocidade média (mph): "; cin >> velocidade;
    cout << "Autonomia (milhas): "; cin >> autonomia;

    aeronaves.push_back(new Aeronave(codigo, modelo, capacidade, velocidade, autonomia));
    cout << "Aeronave cadastrada com sucesso!\n";
}

void Sistema::cadastrarPessoa() {
    int tipo;
    cout << "1. Piloto\n2. Passageiro\nEscolha: ";
    cin >> tipo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (tipo == 1) {
        string nome, matricula, breve;
        int horas;
        cout << "Nome: "; getline(cin, nome);
        cout << "Matrícula: "; getline(cin, matricula);
        cout << "Brevê: "; getline(cin, breve);
        cout << "Horas de voo: "; cin >> horas;
        pilotos.push_back(new Piloto(nome, matricula, breve, horas));
        cout << "Piloto cadastrado!\n";
    } else if (tipo == 2) {
        string nome, cpf, bilhete;
        cout << "Nome: "; getline(cin, nome);
        cout << "CPF: "; getline(cin, cpf);
        cout << "Bilhete: "; getline(cin, bilhete);
        passageiros.push_back(new Passageiro(nome, cpf, bilhete));
        cout << "Passageiro cadastrado!\n";
    } else {
        cout << "Tipo inválido.\n";
    }
}

void Sistema::criarVoo() {
    string cod, origem, destino, hora;
    double distancia;
    int idxAeronave, idxComandante, idxOficial;

    cout << "Código do voo: "; cin >> cod;
    cout << "Origem: "; cin >> origem;
    cout << "Destino: "; cin >> destino;
    cout << "Distância (milhas): "; cin >> distancia;
    cout << "Hora de saída: "; cin >> hora;

    cout << "Aeronaves disponíveis:\n";
    for (size_t i = 0; i < aeronaves.size(); ++i)
        cout << i << ": " << aeronaves[i]->getModelo() << "\n";
    cout << "Escolha a aeronave (índice): "; cin >> idxAeronave;

    cout << "Pilotos disponíveis:\n";
    for (size_t i = 0; i < pilotos.size(); ++i)
        cout << i << ": " << pilotos[i]->getNome() << "\n";
    cout << "Comandante (índice): "; cin >> idxComandante;
    cout << "Primeiro Oficial (índice): "; cin >> idxOficial;

    Voos* voo = new Voos(cod, origem, destino, distancia, aeronaves[idxAeronave], pilotos[idxComandante], pilotos[idxOficial], hora);
    voos.push_back(voo);
    cout << "Voo criado com sucesso!\n";
}

void Sistema::associarPassageiro() {
    string codVoo;
    cout << "Código do voo: "; cin >> codVoo;

    Voos* voo = nullptr;
    for (Voos* v : voos) {
        if (v->getCodigo() == codVoo) {
            voo = v;
            break;
        }
    }

    if (!voo) {
        cout << "Voo não encontrado.\n";
        return;
    }

    cout << "Passageiros disponíveis:\n";
    for (size_t i = 0; i < passageiros.size(); ++i)
        cout << i << ": " << passageiros[i]->getNome() << "\n";
    cout << "Índice do passageiro: ";
    int idx;
    cin >> idx;

    if (voo->vooCheio()) {
        cout << "Voo já está cheio.\n";
    } else {
        voo->adicionarPassageiro(passageiros[idx]);
        cout << "Passageiro associado ao voo.\n";
    }
}

void Sistema::listarVoos() {
    for (Voos* v : voos)
        cout << v->resumoVoo() << "\n";
}

void Sistema::listarPassageirosVoo() {
    string cod;
    cout << "Código do voo: "; cin >> cod;
    for (Voos* v : voos) {
        if (v->getCodigo() == cod) {
            cout << "Aeronave: " << v->getAeronave()->getModelo() << "\n";
            for (Passageiro* p : v->getPassageiros())
                cout << " - " << p->getNome() << "\n";
            return;
        }
    }
    cout << "Voo não encontrado.\n";
}

void Sistema::salvarDados() {
    ofstream fAeronaves("aeronaves.csv");
    for (auto a : aeronaves)
        fAeronaves << a->getCodigo() << "," << a->getModelo() << "," << a->getCapacidade() << ","
                   << a->getVelocidadeMedia() << "," << a->getAutonomia() << "\n";
    fAeronaves.close();

    ofstream fPilotos("pilotos.csv");
    for (auto p : pilotos)
        fPilotos << p->getNome() << "," << p->getMatricula() << "," << p->getBreve() << "," << p->getHorasVoo() << "\n";
    fPilotos.close();

    ofstream fPassageiros("passageiros.csv");
    for (auto p : passageiros)
        fPassageiros << p->getNome() << "," << p->getCPF() << "," << p->getBilhete() << "\n";
    fPassageiros.close();

    ofstream fVoos("voos.csv");
    for (auto v : voos)
        fVoos << v->getCodigo() << "," << v->getOrigem() << "," << v->getDestino() << ","
              << v->getHoraSaida() << "," << v->getAeronave()->getCodigo() << ","
              << v->getComandante()->getMatricula() << "," << v->getPrimeiroOficial()->getMatricula() << "\n";
    fVoos.close();

    cout << "Dados salvos com sucesso!\n";
}

void Sistema::carregarDados() {
    ifstream fAeronaves("aeronaves.csv");
    string linha;
    while (getline(fAeronaves, linha)) {
        stringstream ss(linha);
        string cod, modelo;
        int cap;
        double vel, aut;
        getline(ss, cod, ','); getline(ss, modelo, ',');
        ss >> cap; ss.ignore(); ss >> vel; ss.ignore(); ss >> aut;
        aeronaves.push_back(new Aeronave(cod, modelo, cap, vel, aut));
    }
    fAeronaves.close();

    ifstream fPilotos("pilotos.csv");
    while (getline(fPilotos, linha)) {
        stringstream ss(linha);
        string nome, mat, breve;
        int horas;
        getline(ss, nome, ','); getline(ss, mat, ','); getline(ss, breve, ','); ss >> horas;
        pilotos.push_back(new Piloto(nome, mat, breve, horas));
    }
    fPilotos.close();

    ifstream fPassageiros("passageiros.csv");
    while (getline(fPassageiros, linha)) {
        stringstream ss(linha);
        string nome, cpf, bilhete;
        getline(ss, nome, ','); getline(ss, cpf, ','); getline(ss, bilhete, ',');
        passageiros.push_back(new Passageiro(nome, cpf, bilhete));
    }
    fPassageiros.close();

    cout << "Dados carregados com sucesso!\n";
}

void Sistema::gerarRelatorios() {
    cout << "--- RELATÓRIOS ---\n";
    cout << "Total de voos: " << voos.size() << "\n";
    double somaPassageiros = 0;
    for (auto v : voos)
        somaPassageiros += v->getPassageiros().size();

    cout << "Média de passageiros por voo: "
         << (voos.empty() ? 0 : somaPassageiros / voos.size()) << "\n";

    cout << "Voos com mais de 90% da capacidade:\n";
    for (auto v : voos) {
        if (v->getPassageiros().size() >= 0.9 * v->getAeronave()->getCapacidade())
            cout << "- " << v->getCodigo() << " (" << v->getPassageiros().size() << " passageiros)\n";
    }
}

void Sistema::adicionarAeronave(const string& codigo, const string& modelo, int capacidade, double velocidade, double autonomia) {
    aeronaves.push_back(new Aeronave(codigo, modelo, capacidade, velocidade, autonomia));
}

void Sistema::adicionarPiloto(const string& nome, const string& matricula, const string& breve, int horas) {
    pilotos.push_back(new Piloto(nome, matricula, breve, horas));
}

void Sistema::adicionarPassageiro(const string& nome, const string& cpf, const string& bilhete) {
    passageiros.push_back(new Passageiro(nome, cpf, bilhete));
}

vector<string> Sistema::obterResumoVoos() const {
    vector<string> resumo;
    for (auto v : voos)
        resumo.push_back(v->resumoVoo());
    return resumo;
}

string Sistema::listarPassageirosDeVoo(const string& codigoVoo) const {
    for (auto v : voos) {
        if (v->getCodigo() == codigoVoo) {
            stringstream ss;
            for (auto p : v->getPassageiros())
                ss << p->getNome() << "\n";
            return ss.str();
        }
    }
    return "Voo não encontrado.";
}

string Sistema::gerarRelatorioTexto() const {
    stringstream ss;
    ss << "Total de voos: " << voos.size() << "\n";
    double soma = 0;
    for (auto v : voos) soma += v->getPassageiros().size();
    ss << "Média de passageiros: " << (voos.empty() ? 0 : soma / voos.size()) << "\n";
    ss << "Voos com > 90% capacidade:\n";
    for (auto v : voos) {
        if (v->getPassageiros().size() >= 0.9 * v->getAeronave()->getCapacidade())
            ss << "- " << v->getCodigo() << " (" << v->getPassageiros().size() << " passageiros)\n";
    }
    return ss.str();
}

void Sistema::adicionarVoo(Voos* v) {
    voos.push_back(v);
}

