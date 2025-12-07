#ifndef MOTO_H
#define MOTO_H
#include "Veiculo.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>


class Moto:public Veiculo{

public:
    Moto();
    Moto(string tipo, string marca, string model, string cor, float diaria, bool disponivel);

    

    //static permite chamar o metodo criarLista() sem precisar criar um objeto; variavel preserva o conteudo entre chamada de funcoes.
    //string& evitar copias, apenas "mover" as info de Veiculos
    //vector<Veiculo*> ponmteiros pq a funcao retorna um vetor, apontando o endereco que esse vetor se encontra ;
    static vector<Moto*> lerLista(const string& nomeArquivo);
    static void imprimirLista(const vector<Moto*>& lista);
    void infoVeiculos() const override;

};





#endif
