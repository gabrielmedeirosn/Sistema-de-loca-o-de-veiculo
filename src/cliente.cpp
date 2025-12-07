#include "cliente.h"

Cliente::Cliente() : nome(""), cpf(""), veiculoEscolhido(NULL) {
}

Cliente::Cliente(const string &nome, const string &cpf) : nome(nome), cpf(cpf), veiculoEscolhido(NULL) // NULL pq nenhum veiculo  foi selecionado ainda
{
}

string Cliente::getNome() const{
    return nome;
}

string Cliente::getCpf() const{
    return cpf;
}


void Cliente::setVeiculoEscolhido(Veiculo  *v){
    veiculoEscolhido = v;
}

Veiculo *Cliente::getVeiculoEscolhido() const{
    return veiculoEscolhido;
}

void Cliente::infoCliente() const{
    cout << "Nome: " << nome << endl 
         << "CPF: " << cpf << endl;
    if(veiculoEscolhido){
        cout << "Veiculo Selecionado" << endl;
        veiculoEscolhido -> infoVeiculos();
    }
    else {
        cout  << "Nenhum Veiculo selecionado, tente novamente";
    }
}
