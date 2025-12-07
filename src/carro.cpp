#include "carro.h"
using namespace std;
Carro::Carro() : Veiculo() {

}

Carro::Carro(string tipo, string marca, string model, string cor, float diaria,  bool disponivel) : Veiculo("Carro", marca, model, cor, diaria, disponivel){
}

vector<Carro*> Carro::lerLista(const string &carrosTxt){  //carrosTxt se refere ao nome do arquivo que vai ser aberto

    vector<Carro*> lista; //lista eh o vetor que armazena os carros

    ifstream arquivoTxt("../data/" + carrosTxt); //entrada de dados, criando obejto arquivoTxt responsavel por abrir, ler e fechar(como um scanner)

    try{
        if(!arquivoTxt.is_open()){
            throw runtime_error("Erro ao abrir arquivo: " + carrosTxt);
        }
    

    string marcaTxt, modeloTxt, corTxt;
    bool isDisponivel;
    float diariaTxt;

    while(arquivoTxt >> marcaTxt >> modeloTxt >> corTxt >> diariaTxt >> isDisponivel){
        lista.push_back(new Carro ("Carro", marcaTxt, modeloTxt, corTxt, diariaTxt, isDisponivel));
    }

    arquivoTxt.close();
}
    catch (const exception& e) {
        cout << "Erro: " << e.what() << endl;
    }
    
    return lista;
    
}

void Carro::imprimirLista(const vector<Carro*> &lista){
    cout << "*****Lista de Carros*****" << endl;;
    for(size_t i=0; i<lista.size(); i++){
        cout << i+1 << ". " << lista[i]-> getMarca() << ", "<< lista[i]-> getModel() << ", "<< lista[i]-> getCor() 
            << ", "<< lista[i]-> getDiaria() << ", "
            << (lista[i]-> isDisponivel() ? "Disponivel" : "Indisponivel")
            << endl;
    }
}

void Carro::infoVeiculos() const{
    cout << "*****Informacoes do Carro*****" << endl;
    Veiculo::infoVeiculos();
}