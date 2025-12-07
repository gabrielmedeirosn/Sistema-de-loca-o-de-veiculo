#ifndef CARRO_H
#define CARRO_H
#include "Veiculo.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>


class Carro:public Veiculo{

public:
    Carro();
    Carro(string tipo, string marca, string model, string cor, float diaria, bool disponivel);

    
    //static permite chamar o metodo criarLista() sem precisar criar um objeto; variavel preserva o conteudo entre chamada de funcoes.
    //string& evitar copias, apenas "mover" as info de Veiculos
    //vector<Veiculo*> ponmteiros pq a funcao retorna um vetor, apontando o endereco que esse vetor se encontra ;
    static vector<Carro*> lerLista(const string& nomeArquivo);
    static void imprimirLista(const vector<Carro*>& lista);
    void infoVeiculos() const override;

};


#endif