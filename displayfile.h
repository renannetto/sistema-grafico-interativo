#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H

#include "figura.h"
#include <sstream>
#include <string>
#include <list>

using std::list;

class DisplayFile
{
public:
    DisplayFile();
    ~DisplayFile();
    string adicionarFigura(Tipo, list<Ponto*> pontos);
    list<Figura*> obterFiguras();
    void destruirFigura(string);
    void construirEixosNaOrigem();
private:
    int nPontos;
    int nRetas;
    int nPoligonos;
    list<Figura*> figuras;
};

#endif // DISPLAYFILE_H
