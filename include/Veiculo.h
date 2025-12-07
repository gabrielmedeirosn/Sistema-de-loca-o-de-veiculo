#ifndef VEICULO_H
#define VEICULO_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Veiculo {
protected:
    std::string tipo;
    std::string marca;
    std::string model;
    std::string cor;
    float diaria;
    bool disponivel;

public:
    Veiculo(); //construtor
    Veiculo(std::string tipo, std::string marca, std::string model, std::string cor, float diaria, bool disponivel);

    std::string getTipo() const; //const usado para garantirr que nao vai haver alteracao de dados
    std::string getMarca() const;
    std::string getModel() const;
    std::string getCor() const;
    float getDiaria () const;
    bool isDisponivel () const;
    
    void setDisponivel (bool status);
    
    virtual void infoVeiculos() const;  //imprimir infos do veiculo \\ Função virtual (para polimorfismo)

    /*// Sobrecarga do operador <<
    friend ostream& operator<<(ostream& os, const Veiculo& v);*/



};

#endif
