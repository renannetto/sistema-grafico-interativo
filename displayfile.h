#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H

#include "figura.h"
#include <sstream>
#include <string>
#include <list>

#define PI 3.14159265;

using std::list;

class DisplayFile
{
public:
    DisplayFile();
    ~DisplayFile();
    Figura* criarWindow();
    string adicionarFigura(Tipo, list<Ponto*> pontos, Cor cor);
    list<Figura*> obterFiguras();
    void destruirFigura(string);
    void construirEixosNaOrigem();
    double obterAnguloDaWindow();
private:
    int nPontos;
    int nRetas;
    int nPoligonos;
    list<Figura*> figuras;
    Figura* window;
};

#endif // DISPLAYFILE_H
