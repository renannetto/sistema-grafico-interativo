#ifndef FIGURA_H
#define FIGURA_H

#include <list>
#include "ponto.h"

using namespace std;

class Figura
{
public:
    Figura(list<Ponto*> vPontos);
    ~Figura();
    list<Ponto*> getPontos();
private:
    list<Ponto*> pontos;
};

#endif // FIGURA_H
