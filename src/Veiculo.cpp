#include "Veiculo.h"

Veiculo::Veiculo(){
}

Veiculo::Veiculo(string tipo, string marca, string model, string cor, float diaria, bool disponivel) : 
tipo(tipo), marca(marca), model(model), cor(cor), diaria(diaria), disponivel(disponivel){
}

string Veiculo::getTipo() const{
    return this->tipo;
}

string Veiculo::getMarca() const{
    return this->marca;
}

string Veiculo::getModel() const{
    return this->model;
}

string Veiculo::getCor() const{
    return cor;
}

float Veiculo::getDiaria() const{
    return this->diaria;
}

bool Veiculo::isDisponivel() const{
    return disponivel;
}

void Veiculo::setDisponivel(bool status){
    disponivel = status;
}

void Veiculo::infoVeiculos() const{
    cout << "Tipo......: "  << tipo << endl;
    cout << "Marca.....: "  << marca << endl;
    cout << "Modelo....: "  << model << endl;
    cout << "Diaria....: R$ "  << diaria << endl;
    cout << "COR.......: "  << cor << endl;
    if(disponivel == true){
        cout << 
        "*****Reserva feita.*****" <<  endl;
    }
    else{
        cout << 
        "*****O veiculo nao esta disponivel*****" << endl;
    }
    
}

/*ostream &operator<<(ostream &os, const Veiculo &v)
{
    // ODO: insert return statement here
}*/
