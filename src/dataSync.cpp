#include "dataSync.h"
#include <iostream>
#include <chrono> //uma forma de "calendario"
#include <ctime> //obter data/hora
#include <iomanip>

std::string dataSync::dataUsuario(){

    std::string dia, mes, ano;
    std::cout << "Digite o dia: ";
    std::cin >> dia;
    std::cout << "Digite o mes: ";
    std::cin >> mes;
    std::cout << "Digite o ano: ";
    std::cin >> ano;

    return dia + "/" + mes + "/" + ano;

}

std::string dataSync::getDataAtual() //a forma usada para calcular data eh atraves dos segundos de Epoch
{
    //time_t usado para calcular o valor epoch
    std::time_t dataSecAgora = std::time(nullptr);

    //tm* -> struct definida pelo ctime que define os valores da data e hora || localtime converte para um valor legivel d/m/a
    //tm salva os dados separadamente(D,M,A)

    std::tm* dataAgora = std::localtime(&dataSecAgora);

    char buffer[11];   //DD/MM/AAAA + \0

    //a func snprintf alem de printar tbm salva os valores de dataAgora
    std::snprintf(buffer, sizeof(buffer), "%02d/%02d/%04d",
        dataAgora->tm_mday, dataAgora->tm_mon + 1, dataAgora->tm_year + 1900);
    return std::string(buffer);
}

std::string dataSync::setDataAluguel(){
    char opc;
    std::cout << "Deseja usar a data de hoje (" << getDataAtual() << ")? [s/n]: ";
    std::cin >> opc;

    if (opc == 's' || opc == 'S')
        return getDataAtual();

    return dataUsuario();
}

//SOMAR OS DIAS PARA A DEVOLUCAO
    std::string dataSync::somarDias(const std::string& dataInicial, int diasAdd){
    int dia,mes,ano;

    //extrair dia,mes e ano -> .c_str() "converte" o tipo de leitura usado no C para o C++
    std::sscanf (dataInicial.c_str(), "%d/%d/%d", &dia, &mes, &ano);
    std::tm calendario{};
    calendario.tm_mday = dia;
    calendario.tm_mon  = mes - 1;       
    calendario.tm_year = ano - 1900;

    //convertendo data para sec
    std::time_t segundos = std::mktime(&calendario);

    //converte dias a serem somados em sec
    //static_cast converte os dias em time_t evita overflow em caso de muitos dias
    segundos += static_cast<std::time_t>(diasAdd) * 24 * 60 * 60;
    
    //localtime convertendo os sec para data padrao -> 
    std::tm* novaData = std::localtime(&segundos);

    char buffer[11];
    std::snprintf(buffer, sizeof(buffer), "%02d/%02d/%04d",
        novaData->tm_mday, novaData->tm_mon + 1, novaData->tm_year + 1900
    );

    return std::string(buffer);

}