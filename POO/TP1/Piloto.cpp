#include "Piloto.hpp"

Piloto::Piloto() : Pessoa("") {
    this->matricula = 0;
    this->breve = "";
    this->horasVoo = 0;
}

Piloto::Piloto(string nome, string matricula, string breve, int horasVoo)
    : Pessoa(nome), matricula(stoi(matricula)), breve(breve), horasVoo(horasVoo) {}

string Piloto::getMatricula() const {
    return to_string(matricula);
}

string Piloto::getBreve() const {
    return breve;
}

int Piloto::getHorasVoo() const {
    return horasVoo;
}

void Piloto::setMatricula(string a) {
    matricula = stoi(a);
}

void Piloto::setBreve(string a) {
    breve = a;
}

void Piloto::setHorasVoo(int a) {
    horasVoo = a;
}
