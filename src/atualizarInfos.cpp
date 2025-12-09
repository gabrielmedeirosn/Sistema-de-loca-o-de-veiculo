#include "atualizarInfos.h"
#include "contrato.h"
#include "Veiculo.h"


void listaAlugados::veiculosAlugados(const Veiculo* veiculo, const std::string& dataRetirada, const std::string& dataDevolucao){
    
    std::string pastaAlugados = "Veiculos Alugados";
    
    if (!std::filesystem::exists(pastaAlugados)) {
        std::filesystem::create_directory(pastaAlugados);
    }
    
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    char dataNomeArquivo[20];
    std::snprintf(dataNomeArquivo, sizeof(dataNomeArquivo), "%02d-%02d-%04d_%02d-%02d-%02d",
    now->tm_mday, now->tm_mon + 1, now->tm_year + 1900, now->tm_hour, now->tm_min, now->tm_sec);

    std::string caminhoArq = pastaAlugados + "/" + veiculo->getModel() + "_" + dataNomeArquivo + ".txt";


    std::ofstream alugadosTxt (caminhoArq);
    if(!alugadosTxt.is_open()){
        system("cls");
        cout << "Erro ao gerar contrato, reinicie o programa e tente novamente" << endl;
        return;
    };

    alugadosTxt << veiculo->getMarca() << " " << veiculo->getModel() << " " << veiculo->getCor() << " " <<  veiculo->getDiaria() << " " << dataRetirada << " " << dataDevolucao
    << endl;
    alugadosTxt.close();
}

//void listaAlugados::atualizarDisp(){}

/*int listaAlugados::converterDias(const std::string &tempo)
{
    return 0;
}*/
