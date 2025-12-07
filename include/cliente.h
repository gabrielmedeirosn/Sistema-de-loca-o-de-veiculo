#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <string>
#include <cctype>
#include "Veiculo.h"

/*using std::cin;
using std::cout;
using std::endl;*/

class Cliente{

private:
    string nome;
    string cpf;
    Veiculo* veiculoEscolhido;

public:
    Cliente(); //construtor padrao
    Cliente(const string &nome, const string &cpf); //construtor parametizado

    string getNome() const;
    string getCpf() const;
    
    void setVeiculoEscolhido();
    Veiculo* getVeiculoEscolhido() const;
    

    void setVeiculoEscolhido(Veiculo* v);
    void infoCliente() const;

};

#endif