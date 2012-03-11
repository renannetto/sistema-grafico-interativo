#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H

#include "figura.h"

class DisplayFile
{
public:
    DisplayFile();
    void addFigure(list<Ponto*> pontos);
private:
    list<Figura*> figuras;
};

#endif // DISPLAYFILE_H
