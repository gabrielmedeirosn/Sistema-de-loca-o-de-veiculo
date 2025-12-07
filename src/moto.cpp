#include "moto.h"

Moto::Moto() : Veiculo() {

}

Moto::Moto(string tipo, string marca, string model, string cor, float diaria, bool disponivel): Veiculo("Moto", marca, model, cor, diaria, disponivel){
}


vector<Moto*> Moto::lerLista(const string &MotoTxt){
     vector<Moto*> lista; //lista eh o vetor que armazena as Motos

    ifstream arquivoTxt("../data/" + MotoTxt); //entrada de dados, criando obejto arquivoTxt responsavel por abrir, ler e fechar(como um scanner)

    try{
        if(!arquivoTxt.is_open()){
            throw runtime_error("Erro ao abrir arquivo: " + MotoTxt);
        }
    

    string marcaTxt, modeloTxt, corTxt;
    bool isDisponivelTxt;
    float diariaTxt;

    while(arquivoTxt >> marcaTxt >> modeloTxt >> corTxt >> diariaTxt >> isDisponivelTxt){
        lista.push_back(new Moto ("Moto", marcaTxt, modeloTxt, corTxt, diariaTxt, isDisponivelTxt));
    }

    arquivoTxt.close();
}
    catch (const exception& e) {
        cout << "Erro: " << e.what() << endl;
    }
    
    return lista;
}

void Moto::imprimirLista(const vector<Moto*> &lista){
    cout << "*****Lista de Motos*****" << endl;;
    for(size_t i=0; i<lista.size(); i++){
        cout << i+1 << ". " << lista[i]-> getMarca() << ", "<< lista[i]-> getModel() << ", "<< lista[i]-> getCor() 
            << ", "<< lista[i]-> getDiaria() << ", "
            << (lista[i]-> isDisponivel() ? "Disponivel" : "Indisponivel")
            << endl;
    }
}

void Moto::infoVeiculos() const{
    cout << "*****Informacoes da Moto*****" << endl;
    Veiculo::infoVeiculos();
}