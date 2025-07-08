#include "Voos.hpp"
#include <iostream>
#include <iostream>  // Para entrada e saída padrão
#include <vector>    // Para usar vetores
#include <string>    // Para usar strings
#include <iomanip>
using namespace std;

Voos::Voos(const string &cod, const string &org, const string &dest, double dist,
         Aeronave *a, Piloto *com, Piloto *prim, const string &hora)
    : codigo(cod), origem(org), destino(dest), distancia(dist),
      aeronave(a), comandante(com), primeiroOficial(prim), horaSaida(hora)
{
    escalas = static_cast<int>(dist / a->getAutonomia());
}

void Voos::adicionarPassageiro(Passageiro *p)
{
    if ((int)passageiros.size() < aeronave->getCapacidade())
        passageiros.push_back(p);
}

void Voos::listarPassageiros() const
{
    for (const auto &p : passageiros)
        cout << p->getNome() << endl;
}

void Voos::detalhesVoo() const
{
    cout << "Voo " << codigo << " de " << origem << " para " << destino << " com "
              << passageiros.size() << " passageiros." << endl;
}

Voos *Voos::criarVoo()
{
    string codigo, origem, destino, hora;
    double distancia;

    cout << "\n===== Cadastro de Voo =====\n";
    cout << "Código do Voo: ";
    cin >> codigo;
    cout << "Origem: ";
    cin >> origem;
    cout << "Destino: ";
    cin >> destino;
    cout << "Distância (milhas): ";
    cin >> distancia;
    cout << "Hora de saída: ";
    cin >> hora;

    cout << "Dados da Aeronave:\n";
    string codAeronave, modelo;
    int capacidade;
    double velocidade, autonomia;
    cout << "Código: ";
    cin >> codAeronave;
    cout << "Modelo: ";
    cin >> modelo;
    cout << "Capacidade: ";
    cin >> capacidade;
    cout << "Velocidade média (mph): ";
    cin >> velocidade;
    cout << "Autonomia (milhas): ";
    cin >> autonomia;
    Aeronave *a = new Aeronave(codAeronave, modelo, capacidade, velocidade, autonomia);

    cout << "Dados do Comandante:\n";
    string nomeCom, matCom, breveCom;
    int horasCom;
    cout << "Nome: ";
    cin.ignore();
    getline(cin, nomeCom);
    cout << "Matrícula: ";
    getline(cin, matCom);
    cout << "Brevê: ";
    getline(cin, breveCom);
    cout << "Horas de voo: ";
    cin >> horasCom;
    Piloto *comandante = new Piloto(nomeCom, matCom, breveCom, horasCom);

    cout << "Dados do Primeiro Oficial:\n";
    string nomePO, matPO, brevePO;
    int horasPO;
    cin.ignore();
    cout << "Nome: ";
    getline(cin, nomePO);
    cout << "Matrícula: ";
    getline(cin, matPO);
    cout << "Brevê: ";
    getline(cin, brevePO);
    cout << "Horas de voo: ";
    cin >> horasPO;
    Piloto *primeiroOficial = new Piloto(nomePO, matPO, brevePO, horasPO);

    Voos *voo = new Voos(codigo, origem, destino, distancia, a, comandante, primeiroOficial, hora);

    cout << "\nCadastro de Passageiros (digite 0 para parar):\n";
    for (int i = 0; i < capacidade; ++i)
    {
        string nome, cpf, bilhete;
        cin.ignore();
        cout << "\nPassageiro " << i + 1 << "\n";
        cout << "Nome: ";
        getline(cin, nome);
        if (nome == "0")
            break;
        cout << "CPF: ";
        getline(cin, cpf);
        cout << "Bilhete: ";
        getline(cin, bilhete);
        Passageiro *p = new Passageiro(nome, cpf, bilhete);
        voo->adicionarPassageiro(p);
    }

    return voo;
}

 string Voos::getCodigo() const { return codigo; }
    string Voos::getOrigem() const { return origem; }
    string Voos::getDestino() const { return destino; }
    string Voos::getHoraSaida() const { return horaSaida; }
    Aeronave* Voos::getAeronave() const { return aeronave; }
    Piloto* Voos::getComandante() const { return comandante; }
    Piloto* Voos::getPrimeiroOficial() const { return primeiroOficial; }
    vector<Passageiro*> Voos::getPassageiros() const { return passageiros; }

    bool Voos::vooCheio() const {
        return static_cast<int>(passageiros.size()) >= aeronave->getCapacidade();
    }

    string Voos::resumoVoo() const {
        ostringstream oss;
        oss << "Voo " << codigo << " | Origem: " << origem << " | Destino: " << destino
            << " | Saída: " << horaSaida << " | Passageiros: " << passageiros.size();
        return oss.str();
    }
