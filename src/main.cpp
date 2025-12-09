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

bool cpfJaCadastrado(const string &cpf);

const string ARQ_CLIENTES = "data/clientes.txt";

void salvarClienteEmArquivo(const string &nome, const string &cpf, int tema)
{
    ofstream arq(ARQ_CLIENTES, ios::app);
    if (!arq.is_open())
    {
        throw runtime_error("Nao foi possivel abrir o arquivo de clientes.");
    }

    // formato: CPF;NOME;TEMA
    arq << cpf << ';' << nome << ';' << tema << '\n';
}

string justNumeros(const string &cpf)
{
    string cpfLimpo;

    for (char c : cpf)
    {
        if (isdigit(c))
        {
            cpfLimpo += c;
        }
    }
    return cpfLimpo;
}

string ConfirmaCpf()
{
    string cpf;
    cin >> cpf;

    string cpfLimpo = justNumeros(cpf);

    if (cpfLimpo.length() != 11)
    {
        cout << "CPF digitado incorretamente, Tente novamente: ";
        return ConfirmaCpf();
    }
    return cpfLimpo;
}

string maiusculo(string texto)
{
    for (int i = 0; i < (int)texto.length(); i++)
    {
        texto[i] = toupper(texto[i]);
    }
    return texto;
}

Cliente cadastrarCliente()
{
    string nome, tempNome;
    string cpf;

    cout << "Ola, bem vindo a LocProg" << endl
         << "Siga o passo a passo para escolher seu veiculo desejado" << endl
         << endl;

    cout << "DIGITE SEU NOME: ";
    getline(cin, tempNome);
    nome = maiusculo(tempNome);

    // =======================
    // ESCOLHA DE TEMA AQUI ✅
    // =======================
    int tema = 0;
    while (tema != 1 && tema != 2)
    {
        cout << endl
             << "DIGITE 1 PARA TEMA ESCURO E 2 PARA TEMA CLARO: ";
        cin >> tema;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            tema = 0;
            cout << "Opcao invalida, selecione:" << endl
                 << "1 -> TEMA ESCURO" << endl
                 << "2 -> TEMA CLARO" << endl;
            continue;
        }

        if (tema == 1)
        {
            system("color 0A"); // verde em fundo preto
            system("cls");
        }
        else if (tema == 2)
        {
            system("color F0"); // preto em fundo branco
            system("cls");
        }
        else
        {
            cout << "OPCAO INVALIDA TENTE NOVAMENTE" << endl;
        }
    }

    // limpar \n depois do cin >> tema
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    // =======================
    // CPF + VERIFICAÇÃO DUPLO
    // =======================
    while (true)
    {
        cout << endl
             << "DIGITE SEU CPF: ";
        cpf = ConfirmaCpf();

        try
        {
            if (cpfJaCadastrado(cpf))
            {
                throw runtime_error("Este CPF ja esta cadastrado no sistema!");
            }

            // se chegou aqui, CPF é válido e novo
            salvarClienteEmArquivo(nome, cpf, tema);
            break;
        }
        catch (const exception &e)
        {
            cout << "Erro: " << e.what() << endl;
            cout << "Tente novamente com um CPF diferente." << endl;
        }
    }

    system("cls");
    cout << "CPF confirmado e cadastro realizado com sucesso!" << endl;

    return Cliente(nome, cpf);
}

bool existeClienteNoArquivo(const string &nome, const string &cpf)
{
    ifstream arq(ARQ_CLIENTES);
    if (!arq.is_open())
    {
        throw runtime_error("Nao foi possivel abrir o arquivo de clientes.");
    }

    string linha;
    while (getline(arq, linha))
    {
        if (linha.empty())
            continue;

        size_t sep1 = linha.find(';');
        if (sep1 == string::npos)
            continue;

        size_t sep2 = linha.find(';', sep1 + 1);

        string cpfArquivo = linha.substr(0, sep1);
        string nomeArquivo;

        if (sep2 == string::npos)
        {
            // formato antigo: CPF;NOME
            nomeArquivo = linha.substr(sep1 + 1);
        }
        else
        {
            // formato novo: CPF;NOME;TEMA
            nomeArquivo = linha.substr(sep1 + 1, sep2 - sep1 - 1);
        }

        if (cpfArquivo == cpf && nomeArquivo == nome)
        {
            return true;
        }
    }
    return false;
}

int obterTemaCliente(const string &nome, const string &cpf)
{
    ifstream arq(ARQ_CLIENTES);
    if (!arq.is_open())
    {
        throw runtime_error("Nao foi possivel abrir o arquivo de clientes.");
    }

    string linha;
    while (getline(arq, linha))
    {
        if (linha.empty())
            continue;

        size_t sep1 = linha.find(';');
        if (sep1 == string::npos)
            continue;

        size_t sep2 = linha.find(';', sep1 + 1);

        string cpfArquivo = linha.substr(0, sep1);
        string nomeArquivo;
        int temaArquivo = 1; // padrão: escuro

        if (sep2 == string::npos)
        {
            // formato antigo: CPF;NOME
            nomeArquivo = linha.substr(sep1 + 1);
        }
        else
        {
            // formato novo: CPF;NOME;TEMA
            nomeArquivo = linha.substr(sep1 + 1, sep2 - sep1 - 1);
            if (sep2 + 1 < linha.size())
            {
                try
                {
                    temaArquivo = stoi(linha.substr(sep2 + 1));
                }
                catch (...)
                {
                    temaArquivo = 1;
                }
            }
        }

        if (cpfArquivo == cpf && nomeArquivo == nome)
        {
            return temaArquivo;
        }
    }

    return 1; // se não achar, usa tema escuro como padrão
}

Cliente autenticarCliente()
{
    while (true)
    {
        string tempNome, nome, cpf;

        cout << "DIGITE SEU NOME CADASTRADO: ";
        getline(cin, tempNome);
        nome = maiusculo(tempNome); // padroniza igual ao cadastro

        cout << "DIGITE SEU CPF CADASTRADO: ";
        cpf = ConfirmaCpf();

        // limpando o '\n' que sobra do ConfirmaCpf (que usa >>)
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        try
        {
            if (existeClienteNoArquivo(nome, cpf))
            {
                int tema = obterTemaCliente(nome, cpf);

                if (tema == 1)
                {
                    system("color 0A");
                }
                else if (tema == 2)
                {
                    system("color F0");
                }

                system("cls");
                cout << "Cadastro localizado com sucesso!" << endl;
                return Cliente(nome, cpf);
            }
            else
            {
                cout << "Cadastro nao encontrado para esse nome e CPF." << endl;
                cout << "Deseja tentar novamente? (S/N): ";
                string resp;
                getline(cin, resp);

                if (!resp.empty() && (resp[0] == 'n' || resp[0] == 'N'))
                {
                    system("cls");
                    cout << "Vamos realizar um novo cadastro entao." << endl;
                    return cadastrarCliente();
                }

                system("cls");
            }
        }
        catch (const exception &e)
        {
            cout << "Erro: " << e.what() << endl;
            cout << "Nao foi possivel verificar o cadastro. Vamos tentar de novo." << endl;
        }
    }
}

bool cpfJaCadastrado(const string &cpf)
{
    ifstream arq(ARQ_CLIENTES);
    if (!arq.is_open())
    {
        throw runtime_error("Nao foi possivel abrir o arquivo de clientes.");
    }

    string linha;
    while (getline(arq, linha))
    {
        if (linha.empty())
            continue;

        size_t sep = linha.find(';');
        if (sep == string::npos)
            continue;

        string cpfArquivo = linha.substr(0, sep);

        if (cpfArquivo == cpf)
        {
            return true; // CPF já existe
        }
    }
    return false; // CPF livre
}

int main()
{
    // cout << "Diretorio atual: " << std::filesystem::current_path() << endl;
    system("color 07"); // neutro padrão

    // Pergunta se já tem cadastro
    char possuiCadastro = 0;
    while (true)
    {
        cout << "Possui cadastro no nosso sistema? (S/N): ";
        cin >> possuiCadastro;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Entrada invalida. Digite S para SIM ou N para NAO." << endl;
            continue;
        }

        possuiCadastro = tolower(possuiCadastro);

        if (possuiCadastro == 's' || possuiCadastro == 'n')
        {
            break;
        }

        cout << "Opcao invalida. Digite S para SIM ou N para NAO." << endl;
    }

    // limpar o '\n' antes de usar getline nas funcoes seguintes
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    Cliente cliente = (possuiCadastro == 's')
                          ? autenticarCliente()
                          : cadastrarCliente();

    // cout << endl <<"--------------------------------------------" << endl;
    cout << "Selecione o veiculo desejado" << endl
         << endl;
    cout << "ALUGUEL DE DIVERSAS MOTOS APARTIR DE R$60,00 POR DIA" << endl;
    cout << "Digite 1 para ver as opcoes de Motocicletas" << endl;
    cout << endl
         << "--------------------------------------------" << endl;
    cout << "ALUGUEL DE DIVERSOS CARROS APARTIR DE R$80,00 POR DIA" << endl;
    cout << "Digite 2 para ver as opcoes de CARROS" << endl
         << endl;

    int opcao = 0;

    while (opcao != 1 && opcao != 2)
    {
        cin >> opcao;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(200, '\n');
            opcao = 0;
            cout << "Opcao invalida, selecione:" << endl
                 << "1 -> CARRO" << endl
                 << "2 -> MOTO" << endl;
            continue;
        }
        else
        {
            cout << "OPCAO INVALIDA TENTE NOVAMENTE" << endl;
        }
    }

    system("cls");

    if (opcao == 1)
    {
        vector<Moto *> lista = Moto::lerLista("data/motos.txt");
        if (lista.empty())
            throw std::runtime_error("error 404 motos.txt not found");

        bool selecionadoMoto = false;

        while (!selecionadoMoto)
        {
            try
            {
                Moto::imprimirLista(lista);

                int escolhaCliente;
                cout << endl
                     << "DIGITE O NUMERO DA MOTO DESEJADA: ";

                cin >> escolhaCliente;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(200, '\n');
                    opcao = 0;
                    cout << "Digite um numero valido" << endl;
                    continue;
                }

                if (escolhaCliente < 1 || escolhaCliente > (int)lista.size())
                {
                    system("cls");
                    throw std::runtime_error("OPCAO INVALIDA. TENTE NOVAMENTE.");
                }

                if (lista[escolhaCliente - 1]->isDisponivel())
                {
                    cout << lista[escolhaCliente - 1]->getMarca() << " " << lista[escolhaCliente - 1]->getModel() << endl;

                    string confirmaMoto;
                    cout << "Confirmar escolha? (S/N): ";
                    cin >> confirmaMoto;
                    system("cls");

                    if (tolower(confirmaMoto[0]) == 's')
                    {
                        selecionadoMoto = true;
                        cliente.setVeiculoEscolhido(lista[escolhaCliente - 1]);

                        // marca como alugado
                        lista[escolhaCliente - 1]->setDisponivel(false);
                        Moto::salvarLista(lista, "data/motos.txt");

                        system("cls");
                        cout << "Moto selecionada com sucesso" << endl;
                        lista[escolhaCliente - 1]->infoVeiculos();
                    }
                }
                else
                {
                    system("cls");
                    cout << endl
                         << "Veiculo indisponivel, favor selecionar outro" << endl
                         << endl;
                }
            }
            catch (const exception &e)
            {
                cout << "Erro: " << e.what() << endl
                     << endl;
            }
        }
    }
    else if (opcao == 2)
    {
        vector<Carro *> lista = Carro::lerLista("data/carros.txt");
        if (lista.empty())
            throw runtime_error("error 404 carros.txt not found");

        bool selecionadoCarro = false;

        while (!selecionadoCarro)
        {
            try
            {
                Carro::imprimirLista(lista);

                int escolhaCliente;
                cout << endl
                     << "DIGITE O NUMERO DO CARRO DESEJADO: ";
                cin >> escolhaCliente;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(200, '\n');
                    opcao = 0;
                    cout << "Digite um numero valido" << endl;
                    continue;
                }
                system("cls");
                if (escolhaCliente < 1 || escolhaCliente > (int)lista.size())
                {
                    // system("cls");
                    throw runtime_error("OPCAO INVALIDA. TENTE NOVAMENTE.");
                }

                if (lista[escolhaCliente - 1]->isDisponivel())
                {
                    cout << lista[escolhaCliente - 1]->getMarca() << " "
                         << lista[escolhaCliente - 1]->getModel() << endl;

                    string confirmaCarro;
                    cout << "Confirmar escolha? (S/N): ";
                    cin >> confirmaCarro;

                    if (toupper(confirmaCarro[0]) == 'S')
                    {
                        selecionadoCarro = true;
                        cliente.setVeiculoEscolhido(lista[escolhaCliente - 1]);

                        // marca como alugado
                        lista[escolhaCliente - 1]->setDisponivel(false);
                        Carro::salvarLista(lista, "data/carros.txt");

                        system("cls");
                        cout << "Carro selecionado com sucesso" << endl;
                        lista[escolhaCliente - 1]->infoVeiculos();
                    }
                }
                else
                {
                    system("cls");
                    cout << endl
                         << "Veiculo indisponivel, favor selecionar outro" << endl
                         << endl;
                }
            }
            catch (const exception &e)
            {
                cout << "Erro: " << e.what() << endl
                     << endl;
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
