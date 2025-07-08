#include "Passageiros.hpp"

Passageiro::Passageiro() : Pessoa("") {
    CPF = "";
    numeroBilhete = "";
}

Passageiro::Passageiro(string nome, string CPF, string numeroBilhete)
    : Pessoa(nome), CPF(CPF), numeroBilhete(numeroBilhete) {}

string Passageiro::getCPF() const {
    return CPF;
}

string Passageiro::getBilhete() const {
    return numeroBilhete;
}

void Passageiro::setCPF(string a) {
    CPF = a;
}

void Passageiro::setBilhete(string a) {
    numeroBilhete = a;
}
