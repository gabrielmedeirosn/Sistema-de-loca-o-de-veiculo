#ifndef CONTRATO_H
#define CONTRATO_H

#include <string>
#include "Cliente.h"
#include "Veiculo.h"


class Contrato {
private:
    std::string dataRetirada;
    int diasAluguel;
    bool seguro;
    float valorFinal;
    Cliente cliente;
    Veiculo* veiculo; //ponteiro para apontar o tipo de subclasse

public:
    Contrato(const Cliente& c, Veiculo* v);

    void preencherFormulario();
    void calcularValorFinal();
    void gerarArquivoTxt(const std::string& nomeArquivo) const;
};



#endif