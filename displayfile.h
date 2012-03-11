#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H

#include "figura.h"
#include <sstream>

class DisplayFile
{
public:
    DisplayFile();
    string addFigure(Tipo, list<Ponto*> pontos);
    list<Figura*> getFigures();
private:
    int nPontos;
    int nRetas;
    int nPoligonos;
    list<Figura*> figuras;
};

#endif // DISPLAYFILE_H
