#ifndef CLIPPING_H
#define CLIPPING_H

#include <ponto.h>
#include <list>
#include <iostream>

using namespace std;

class Clipping
{
    enum RC {
        MEIO = 0x0,
        BAIXO = 0x4,
        CIMA = 0x8,
        ESQUERDA = 0x1,
        DIREITA = 0x2,
        CIMAESQUERDA = 0x9,
        CIMADIREITA = 0xA,
        BAIXOESQUERDA = 0x5,
        BAIXODIREITA = 0x6
    };

    enum BORDA {BESQUERDA, BDIREITA, BCIMA, BBAIXO};

public:
    Clipping(double,double,double,double, double);
    bool clippingDePonto(Ponto &);
    bool clippingDeLinhaCohen(Ponto const &, Ponto const &, Ponto &, Ponto &);
    bool clippingDePoligonosWeiler(list<Ponto*> &, list<Ponto*> &);
    bool clippingDePoligonosSutherland(list<Ponto*> &, list<Ponto*> &);
    bool cliparPontosPoligono(BORDA borda, list<Ponto*> &pontos, list<Ponto*> &nPontos);
    void fixarCoordenadas(double xMin, double xMax, double yMin, double yMax, double deslocamento);
    double obterXMin();
    double obterXMax();
    double obterYMin();
    double obterYMax();
private:
    int identificarRC(Ponto const &);
    bool calculaNovoPonto(double, int, Ponto const &, Ponto &);
    bool clippingDeLinhaCohenParaWeiler(Ponto const &, Ponto const &, Ponto &, Ponto &);
    double xMin;
    double xMax;
    double yMin;
    double yMax;
};

#endif // CLIPPING_H
