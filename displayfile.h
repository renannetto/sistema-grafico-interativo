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
    string addFigure(Tipo, list<Ponto*> pontos);
    list<Figura*> getFigures();
    void destructFigure(string);
private:
    int nPontos;
    int nRetas;
    int nPoligonos;
    list<Figura*> figuras;
};

#endif // DISPLAYFILE_H
