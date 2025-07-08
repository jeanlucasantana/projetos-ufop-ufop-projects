#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

#include "Pessoa.hpp"
#include <string>
#include <vector>
using namespace std;

class Passageiro : public Pessoa {
private:
    string CPF;
    string numeroBilhete;

public:
    Passageiro();
    Passageiro(string nome, string CPF, string numeroBilhete);

    string getCPF() const;
    string getBilhete() const;

    void setCPF(string a);
    void setBilhete(string a);
};

#endif
