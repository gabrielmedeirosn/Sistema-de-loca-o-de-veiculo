#include "Contrato.h"
#include "Cliente.h"
#include "Veiculo.h"
#include "dataSync.h"
#include <iostream>
#include <fstream>
#include <filesystem>



Contrato::Contrato(const Cliente &c, Veiculo* v) : cliente(c), veiculo(v), diasAluguel(0), seguro(false), valorFinal(0.0) {}



void Contrato::preencherFormulario(){
    cout << endl << "--------FORMULARIO DE LOCACAO LOCPROG--------" << endl << endl;
    cout << "Data de retirada(DD/MM/AAAA): ";
    //getline(cin, dataRetirada);
    dataRetirada = dataSync::getDataAtual();

    cout << endl << "Quantos dias de aluguel: ";
    cin >> diasAluguel;

    cout << endl << "Aproveite: seguro para qualquer veiculo por R$19,99/dia! " << endl
    << "Inclui protecao completa contra danos a voce e a terceiros. Seguranca total por um preco unico." << endl <<
    "Gostaria de adicionar seguro ao pacote? (S/N)" << endl;
    string respSec;
    cin >> respSec;
    if(toupper(respSec[0]) == 'S'){
        seguro = true;
    }
    calcularValorFinal();
}


void Contrato::calcularValorFinal(){
    valorFinal = veiculo->getDiaria() * diasAluguel;
    if (seguro){
        valorFinal += diasAluguel * 19.99f;
    }

}

void Contrato::gerarArquivoTxt(const string& gerarContrato) const{

    string pastaBase = "Contratos";
    string pastaCliente = pastaBase + "/" + cliente.getCpf();
    if (!std::filesystem::exists(pastaBase)) {
        std::filesystem::create_directory(pastaBase);
    }

    if(!std::filesystem::exists(pastaCliente)){
        std::filesystem::create_directories(pastaCliente);
    }

    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    char timestamp[20];
    std::snprintf(timestamp, sizeof(timestamp), "%02d-%02d-%04d_%02d-%02d-%02d",
    now->tm_mday, now->tm_mon + 1, now->tm_year + 1900, now->tm_hour, now->tm_min, now->tm_sec);

    string nomeArquivo = cliente.getCpf() + "_" + timestamp + ".txt";
    
    string caminhoArq = pastaCliente + "/" + nomeArquivo;

    

    ofstream contratoTxt (caminhoArq);
    if(!contratoTxt.is_open()){
        system("cls");
        cout << "Erro ao gerar contrato, reinicie o programa e tente novamente" << endl;
    }

    system("cls");
    contratoTxt << "==============================" << endl;
    contratoTxt << "      CONTRATO DE LOCPROG     " << endl;
    contratoTxt << "==============================" << endl << endl;

    contratoTxt << "NOME.............: " << cliente.getNome() << endl;
    contratoTxt << "CPF..............: " << cliente.getCpf() << endl;
    contratoTxt << "VEICULO..........: " << veiculo->getMarca() << " " << veiculo->getModel() << endl;
    contratoTxt << "VALOR DA DIARIA..: " << "R$" << veiculo->getDiaria() << endl;

    contratoTxt << "DATA DE RETIRADA.: " << dataRetirada << endl;
    contratoTxt << "DIAS DE LOCACAO..: " << diasAluguel << endl;
    contratoTxt << "Data de devolucao: " << dataSync::somarDias(dataSync::getDataAtual(), diasAluguel) << endl;
    contratoTxt << "SEGURO...........: " ; if(seguro){contratoTxt << "SIM";} else{contratoTxt << "NAO";} contratoTxt << endl;
    contratoTxt << "VALOR FINAL......: R$ " << valorFinal << endl;

    contratoTxt.close();

    cout << endl << "CONTRATO GERADO COM SUCESSO EM: " << std::filesystem::absolute(caminhoArq) << endl;
    cout << "LOCPROG AGRADECE A SUA PREFERENCIA E DESEJA UMA OTIMA EXPECIENCIA" << endl;
    cout << "Precione Enter para encerrar o programa";

}
