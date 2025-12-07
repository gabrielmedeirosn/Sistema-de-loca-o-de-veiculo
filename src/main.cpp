#include "Veiculo.h"
#include "carro.h"
#include "moto.h"
#include "cliente.h"
#include "contrato.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <limits>
#include <filesystem>
using namespace std;

string justNumeros (const string &cpf){
    string cpfLimpo;

    for(char c: cpf){
        if(isdigit(c)){
            cpfLimpo +=c;
        }
    }
    return cpfLimpo;
}

string ConfirmaCpf(){
    string cpf;
    cin >> cpf;

    string cpfLimpo = justNumeros(cpf);

    if(cpfLimpo.length() != 11){
        cout << "CPF digitado incorretamente, Tente novamente: ";
        return ConfirmaCpf();
    }
        return cpfLimpo;
    
}

string maiusculo(string texto) {
    for (int i = 0; i < (int)texto.length(); i++) {
        texto[i] = toupper(texto[i]);
    }
    return texto;
}


int main() {
    cout << "Diretorio atual: " << std::filesystem::current_path() << endl;

    cout << "DIGITE 1 PARA TEMA CLARO E 2 PARA TEMA ESCURO: ";
    int tema;
    cin >> tema;
    if(tema==1){
        system("color f0");
        system ("cls");
    }
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    string nome,tempNome;
    string cpf;
    //vector <Veiculo> veiculoCliente;
    string veiculoEscolhido;

    cout << "Ola, bem vindo a LocProg" << endl << "Siga o passo a passo para escolher seu veiculo desejado"<< endl << endl;
    cout << "DIGITE SEU NOME: ";
    getline(cin,tempNome);
    nome = maiusculo(tempNome);
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl << "DIGITE SEU CPF: ";
    cpf = ConfirmaCpf();
    system ("cls");
    cout << "CPF confirmado"  << endl;

    Cliente cliente(nome,cpf);

    //cout << endl <<"--------------------------------------------" << endl;
    cout << "Selecione o veiculo desejado" << endl  << endl;
    cout  << "ALUGUEL DE DIVERSAS MOTOS APARTIR DE R$60,00 POR DIA" << endl;
    cout << "Digite 1 para ver as opcoes de Motocicletas" << endl;
    cout << endl <<"--------------------------------------------" << endl;
    cout  << "ALUGUEL DE DIVERSOS CARROS APARTIR DE R$80,00 POR DIA" << endl;
    cout << "Digite 2 para ver as opcoes de CARROS" << endl << endl;

    int opcao = 0;
    
    
    while(opcao!=1 && opcao!=2){
        cin >> opcao;
        if(opcao!=1 && opcao!=2){
            cout << endl << "Opcao invalida, tente novamente" << endl;
        }
    }
    
    system ("cls");

    if(opcao == 1) {
        vector<Moto*> lista = Moto::lerLista("../data/motos.txt");
        if (lista.empty()) throw std::runtime_error("error 404 motos.txt not found");

        bool selecionadoMoto = false;

        while(!selecionadoMoto) {
            try {
                Moto::imprimirLista(lista);

                int escolhaCliente;
                cout << endl << "DIGITE O NUMERO DA MOTO DESEJADA: ";
                cin >> escolhaCliente;

                if (escolhaCliente < 1 || escolhaCliente > (int)lista.size()) {
                    system("cls");
                    throw std::runtime_error("OPCAO INVALIDA. TENTE NOVAMENTE.");
                }

                if (lista[escolhaCliente - 1]->isDisponivel()) {
                    cout << lista[escolhaCliente - 1]->getMarca() << " "<< lista[escolhaCliente - 1]->getModel() << endl;

                    string confirmaMoto;
                    cout << "Confirmar escolha? (S/N): ";
                    cin >> confirmaMoto;
                    system("cls");

                    if (tolower(confirmaMoto[0]) == 's') {
                        selecionadoMoto = true;
                        cliente.setVeiculoEscolhido(lista[escolhaCliente - 1]);
                        system("cls");
                        cout << "Moto selecionada com sucesso" << endl;
                        lista[escolhaCliente - 1]->infoVeiculos();
                    }
                } else {
                    system("cls");
                    cout << endl << "Veiculo indisponivel, favor selecionar outro" << endl << endl;
                }

            } catch (const exception &e) {
                cout << "Erro: " << e.what() << endl << endl;
            }
        }
    }
    else if (opcao == 2) {
        vector<Carro*> lista = Carro::lerLista("../data/carros.txt");
        if (lista.empty()) throw runtime_error("error 404 carros.txt not found");

        bool selecionadoCarro = false;

        while(!selecionadoCarro) {
            try {
                Carro::imprimirLista(lista);

                int escolhaCliente;
                cout << endl << "DIGITE O NUMERO DO CARRO DESEJADO: ";
                cin >> escolhaCliente;
                system("cls");
                if (escolhaCliente < 1 || escolhaCliente > (int)lista.size()) {
                    //system("cls");
                    throw runtime_error("OPCAO INVALIDA. TENTE NOVAMENTE.");
                    
                }

                if (lista[escolhaCliente - 1]->isDisponivel()) {
                    cout << lista[escolhaCliente - 1]->getMarca() << " "
                        << lista[escolhaCliente - 1]->getModel() << endl;

                    string confirmaCarro;
                    cout << "Confirmar escolha? (S/N): ";
                    cin >> confirmaCarro;

                    if (toupper(confirmaCarro[0]) == 'S') {
                        selecionadoCarro = true;
                        cliente.setVeiculoEscolhido(lista[escolhaCliente - 1]);
                        system("cls");
                        cout << "Carro selecionado com sucesso" << endl;
                        lista[escolhaCliente - 1]->infoVeiculos();
                    }
                } else {
                    system("cls");
                    cout << endl << "Veiculo indisponivel, favor selecionar outro" << endl << endl;
                }

            } catch (const exception &e) {
                cout << "Erro: " << e.what() << endl << endl;
            }
        }
    }

    cout << "Precione Enter para gerar seu contrato..." << endl;   
    cin.ignore(); 
    cin.get();
    system("cls");

    Contrato contratoCliente(cliente, cliente.getVeiculoEscolhido());
    contratoCliente.preencherFormulario();
    contratoCliente.gerarArquivoTxt("contrato_" + cliente.getCpf() + ".txt");




    cin.ignore(); 
    cin.get();

    return 0;
}
