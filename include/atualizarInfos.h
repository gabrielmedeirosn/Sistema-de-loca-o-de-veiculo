#ifndef ATUALIZARINFOS_H
#define ATUALIZARINFOS_H

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "Veiculo.h"
#include "dataSync.h"
#include "contrato.h"

class listaAlugados{
//criar arquivo com *veiculo - data de aluguel - data de devolucao
//ler data de aluguel e data de devolucao
//caso data de aluguel == data atual -> carro.txt ou  moto.txt vai alterar a disponibilidade para 1
//caso data devolucao < data atual -> vai reescrever a disponibilidade para 1

public:
    static void veiculosAlugados ( 
        const Veiculo* veiculo,
        const std::string& dataRetirada,
        const std::string& dataDevolucao);

    //static void atualizarDisp();


/*private:
    static int converterDias(const std::string& data);

*/
};







#endif