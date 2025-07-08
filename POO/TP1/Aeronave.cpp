#include "Aeronave.hpp"

// Construtor padrão
Aeronave::Aeronave() {
    codigo = "";
    modelo = "";
    capacidade = 0;
    velocidadeMedia = 0.0;
    autonomia = 0.0;
}

// Construtor parametrizado
Aeronave::Aeronave(string c, string m, int cap, double vel, double aut) {
    codigo = c;
    modelo = m;
    capacidade = cap;
    velocidadeMedia = vel;
    autonomia = aut;
}

// Destrutor
Aeronave::~Aeronave() {}

// Getters
string Aeronave::getCodigo() const { return codigo; }
string Aeronave::getModelo() const { return modelo; }
int Aeronave::getCapacidade() const { return capacidade; }
double Aeronave::getVelocidadeMedia() const { return velocidadeMedia; }
double Aeronave::getAutonomia() const { return autonomia; }

// Setters
void Aeronave::setCodigo(string cod) {
    if (cod.empty()) throw invalid_argument("Código não pode ser vazio.");
    codigo = cod;
}

void Aeronave::setModelo(string mod) {
    if (mod.empty()) throw invalid_argument("Modelo não pode ser vazio.");
    modelo = mod;
}

void Aeronave::setCapacidade(int cap) {
    if (cap <= 0) throw invalid_argument("Capacidade deve ser positiva.");
    capacidade = cap;
}

void Aeronave::setVelocidadeMedia(double vel) {
    if (vel <= 0) throw invalid_argument("Velocidade média deve ser positiva.");
    velocidadeMedia = vel;
}

void Aeronave::setAutonomia(double aut) {
    if (aut <= 0) throw invalid_argument("Autonomia deve ser positiva.");
    autonomia = aut;
}

// Função para exibir dados da aeronave
void Aeronave::exibirInfo() const {
    cout << "Aeronave [" << codigo << "] - Modelo: " << modelo
         << " | Capacidade: " << capacidade
         << " | Velocidade Média: " << velocidadeMedia
         << " | Autonomia: " << autonomia << endl;
}
