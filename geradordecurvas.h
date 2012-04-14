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
    void gerarBSpline(list<Ponto*> &pontos, list<Ponto*> &nPontos);
    void gerarBSplineBlending(double constantesX[], double constantesY[], list<Ponto*> &nPontos);
    void forwardDifferences(Ponto &ponto, Ponto &delta, Ponto &delta2, Ponto &delta3, list<Ponto*> &nPontos);
private:
    int nPassos;
    double matrizBezier[4][4];
    double matrizBSpline[4][4];
    bool forward;
};

#endif // GERADORDECURVAS_H
