#include "displayfile.h"

DisplayFile::DisplayFile()
{
    nPontos = 0;
    nRetas = 0;
    nPoligonos = 0;
}

string DisplayFile::addFigure(Tipo tipo, list<Ponto*> pontos)
{
    Figura *figura;
    string nome;
    stringstream nomeInt;
    switch(tipo)
    {
        case PONTO: nome = "Ponto";
                    nomeInt << nome << nPontos;
                    nome = nomeInt.str();
                    figura = new Figura(nome, tipo, pontos);
                    nPontos++;
                    break;
        case RETA: nome = "Reta";
                   nomeInt << nome << nRetas;
                   nome = nomeInt.str();
                   figura = new Figura(nome, tipo, pontos);
                   nRetas++;
                   break;
        case POLIGONO: nome = "Poligono";
                       nomeInt << nome << nPoligonos;
                       nome = nomeInt.str();
                       figura = new Figura(nome, tipo, pontos);
                       nPoligonos++;
                       break;
    }
    figuras.push_back(figura);
    return nome;
}

list<Figura*> DisplayFile::getFigures(){
    return figuras;
}
