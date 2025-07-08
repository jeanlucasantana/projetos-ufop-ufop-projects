#include "Pessoa.hpp"

Pessoa::Pessoa() {
    nome = "";
}

Pessoa::Pessoa(string nome) {
    this->nome = nome;
}

Pessoa::~Pessoa() {}

void Pessoa::setNome(string a) {
    nome = a;
}

string Pessoa::getNome() const {
    return nome;
}
