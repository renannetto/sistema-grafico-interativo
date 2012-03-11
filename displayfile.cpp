#include "displayfile.h"

DisplayFile::DisplayFile()
{
}

void DisplayFile::addFigure(list<Ponto*> pontos)
{
    Figura *figura = new Figura(pontos);
    figuras.push_back(figura);
}

list<Figura*> DisplayFile::getFigures(){
    return figuras;
}
