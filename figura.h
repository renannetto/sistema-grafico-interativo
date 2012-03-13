#ifndef FIGURA_H
#define FIGURA_H

#include <list>
#include <string>
#include <math.h>
#include "ponto.h"

using namespace std;

enum Tipo {PONTO, RETA, POLIGONO, EIXO};

class Figura
{
public:
    Figura(string vNome, Tipo vTipo, list<Ponto*> vPontos);
    ~Figura();
    list<Ponto*> obterPontos();
    string obterNome();
    Tipo obterTipo();
    void transaladar2D(double,double);
    void escalonar2D(double,double);
    void rotacionarNaOrigem2D(double);
    void rotacionarNoCentro2D(double);
    void rotacionarNoPonto2D(double,double,double);
private:
    double xMedio;
    double yMedio;
    double** matrizT;
    void transformar2D();
    string nome;
    Tipo tipo;
    list<Ponto*> pontos;
};

#endif // FIGURA_H
