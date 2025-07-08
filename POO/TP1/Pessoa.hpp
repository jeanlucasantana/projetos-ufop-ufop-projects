#ifndef PESSOA_H
#define PESSOA_H

#include <string>
using namespace std;

class Pessoa {
protected:
    string nome;

public:
    Pessoa();                      // construtor padrão
    Pessoa(string nome);          // construtor com nome
    virtual ~Pessoa();            // destrutor virtual
    void setNome(string a);       // setter
    string getNome() const;       // getter
};

#endif
