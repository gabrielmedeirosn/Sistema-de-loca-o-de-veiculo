#ifndef CONTRATO_H
#define CONTRATO_H

#include "atualizarInfos.h"
#include <string>
#include "Cliente.h"
#include "Veiculo.h"


class Contrato {
private:
    
    Cliente cliente;
    Veiculo* veiculo; //ponteiro para apontar o tipo de subclasse
    std::string dataRetirada;
    int diasAluguel;
    bool seguro;
    float valorFinal;
    
    
    

public:
    Contrato(const Cliente& c, Veiculo* v);

    void preencherFormulario();
    void calcularValorFinal();
    void gerarArquivoTxt(const std::string& nomeArquivo) const;

    std::string getDataRetirada() const;
};



#endif