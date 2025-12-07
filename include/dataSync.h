#ifndef DATASYNC_H
#define DATASYNC_H


#include <string>


class dataSync {

    private:
    static std::string dataUsuario();
    
    public:
    static std::string somarDias(const std::string& dataInicial, int diasAdd);
    static std::string getDataAtual();
    static std::string setDataAluguel();

};




#endif