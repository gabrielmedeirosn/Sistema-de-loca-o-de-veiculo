#include "carro.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

Carro::Carro() : Veiculo() {}

Carro::Carro(string tipo, string marca, string model, string cor, float diaria, bool disponivel)
    : Veiculo("Carro", marca, model, cor, diaria, disponivel) {}

vector<Carro *> Carro::lerLista(const string &caminho)
{ // caminho = "data/carros.txt"
    vector<Carro *> lista;

    ifstream arquivoTxt(caminho);

    if (!arquivoTxt.is_open())
    {
        throw runtime_error("Erro ao abrir arquivo: " + caminho);
    }

    string marcaTxt, modeloTxt, corTxt;
    bool isDisponivelTxt;
    float diariaTxt;

    while (arquivoTxt >> marcaTxt >> modeloTxt >> corTxt >> diariaTxt >> isDisponivelTxt)
    {
        lista.push_back(
            new Carro("Carro", marcaTxt, modeloTxt, corTxt, diariaTxt, isDisponivelTxt));
    }

    arquivoTxt.close();
    return lista;
}

void Carro::imprimirLista(const vector<Carro *> &lista)
{
    cout << "***** Lista de Carros *****" << endl;
    for (size_t i = 0; i < lista.size(); i++)
    {
        cout << i + 1 << ". "
             << lista[i]->getMarca() << ", "
             << lista[i]->getModel() << ", "
             << lista[i]->getCor() << ", "
             << lista[i]->getDiaria() << ", "
             << (lista[i]->isDisponivel() ? "Disponivel" : "Indisponivel")
             << endl;
    }
}

void Carro::infoVeiculos() const
{
    cout << "***** Informacoes do Carro *****" << endl;
    Veiculo::infoVeiculos();
}

void Carro::salvarLista(const vector<Carro *> &lista, const string &caminho)
{
    ofstream arq(caminho);
    if (!arq.is_open())
    {
        throw runtime_error("Erro ao salvar arquivo de carros: " + caminho);
    }

    for (const auto &c : lista)
    {
        arq << c->getMarca() << ' '
            << c->getModel() << ' '
            << c->getCor() << ' '
            << c->getDiaria() << ' '
            << (c->isDisponivel() ? 1 : 0) << '\n';
    }

    arq << "/0\n";
}
