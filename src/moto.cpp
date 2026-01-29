#include "moto.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

// Construtor vazio
Moto::Moto() : Veiculo() {}

// Construtor completo
Moto::Moto(string tipo, string marca, string model, string cor, float diaria, bool disponivel)
    : Veiculo("Moto", marca, model, cor, diaria, disponivel) {}

vector<Moto *> Moto::lerLista(const string &caminho)
{
    vector<Moto *> lista;

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
            new Moto("Moto", marcaTxt, modeloTxt, corTxt, diariaTxt, isDisponivelTxt));
    }

    arquivoTxt.close();
    return lista;
}

void Moto::imprimirLista(const vector<Moto *> &lista)
{
    cout << "***** Lista de Motos *****" << endl;

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

void Moto::infoVeiculos() const
{
    cout << "***** Informacoes da Moto *****" << endl;
    Veiculo::infoVeiculos();
}

void Moto::salvarLista(const vector<Moto *> &lista, const string &caminho)
{
    ofstream arq(caminho);
    if (!arq.is_open())
    {
        throw runtime_error("Erro ao salvar arquivo de motos: " + caminho);
    }

    // Reescreve todas as motos
    for (const auto &m : lista)
    {
        arq << m->getMarca() << ' '
            << m->getModel() << ' '
            << m->getCor() << ' '
            << m->getDiaria() << ' '
            << (m->isDisponivel() ? 1 : 0) << '\n';
    }

    // Linha sentinela
    arq << "/0\n";
}
