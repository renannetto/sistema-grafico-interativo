#ifndef GERADORDECURVAS_H
#define GERADORDECURVAS_H

#include "ponto.h"
#include <list>

using namespace std;

class GeradorDeCurvas
{
public:
    GeradorDeCurvas();
    void construirMatrizes();
    void gerarBezier(list<Ponto*> &pontos, list<Ponto*> &nPontos);
private:
    int nPassos;
    double matrizBezier[4][4];
};

#endif // GERADORDECURVAS_H
