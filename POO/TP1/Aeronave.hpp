#ifndef AERONAVE_H
#define AERONAVE_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

class Aeronave {
private:
    string codigo;
    string modelo;
    int capacidade;
    double velocidadeMedia;
    double autonomia;

public:
    Aeronave(); // Construtor padrão
    Aeronave(string c, string m, int cap, double vel, double aut); // Construtor parametrizado
    ~Aeronave(); // Destrutor

    // Getters
    string getCodigo() const;
    string getModelo() const;
    int getCapacidade() const;
    double getVelocidadeMedia() const;
    double getAutonomia() const;

    // Setters
    void setCodigo(string cod);
    void setModelo(string mod);
    void setCapacidade(int cap);
    void setVelocidadeMedia(double vel);
    void setAutonomia(double aut);

    // Utilitários
    void exibirInfo() const;
};

#endif
