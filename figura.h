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
private:
    string nome;
    Tipo tipo;
    list<Ponto*> pontos;
};

#endif // FIGURA_H
