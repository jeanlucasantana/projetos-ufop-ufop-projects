#ifndef PILOTO_H
#define PILOTO_H

#include "Pessoa.hpp"
#include <string>
#include <vector>
using namespace std;

class Piloto : public Pessoa {
private:
    int matricula;
    string breve;
    int horasVoo;

public:
    Piloto();
    Piloto(string nome, string matricula, string breve, int horasVoo);

    string getMatricula() const;
    string getBreve() const;
    int getHorasVoo() const;

    void setMatricula(string a);
    void setBreve(string a);
    void setHorasVoo(int a);
};

#endif
