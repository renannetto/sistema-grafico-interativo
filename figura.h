#ifndef FIGURA_H
#define FIGURA_H

#include <list>
#include <string>
#include "ponto.h"

using namespace std;

enum Tipo {PONTO, RETA, POLIGONO};

class Figura
{
public:
    Figura(string vNome, Tipo vTipo, list<Ponto*> vPontos);
    ~Figura();
    list<Ponto*> getPontos();
    string getNome();
    Tipo getTipo();
    void transaladar2D(double,double);
    void escalonar2D(double,double);
    void rotacionarNaOrigem2D(double);
    void rotacionarNoCentro2D(double);
    void rotacionarNoPonto2D(double,double);
private:
    void transformar2D(double**);
    string nome;
    Tipo tipo;
    list<Ponto*> pontos;
};

#endif // FIGURA_H
