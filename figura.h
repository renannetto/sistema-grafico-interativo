#ifndef FIGURA_H
#define FIGURA_H

#include <list>
#include <string>
#include <math.h>
#include "ponto.h"
#include "cor.h"

using namespace std;

enum Tipo {CURVASPLINE, CURVABEZIER, PONTO, RETA, POLIGONO, POLIGONOPREENCHIDO, EIXO, WINDOW};

class Figura
{
public:
    Figura(string vNome, Tipo vTipo, list<Ponto*> vPontos, Cor vCor, double wcX, double wcY, double teta);
    ~Figura();
    list<Ponto*> obterPontos();
    list<Ponto*> obterPontosPPC();
    string obterNome();
    Tipo obterTipo();
    Cor obterCor();
    void transladar(double,double);
    void escalonar(double,double);
    void rotacionar(double);
    void rotacionarNaOrigem2D(double);
    void rotacionarNoCentro2D(double);
    void rotacionarNoPonto2D(double,double,double);
    void mudarCor(int, int, int);
    void gerarDescricaoPPC(double wcX, double wcY, double teta);
    Ponto obterCentro();
private:
    double** matrizT;
    void transformar();
    string nome;
    Tipo tipo;
    list<Ponto*> pontos;
    list<Ponto*> pontosPPC;
    Cor cor;
};

#endif // FIGURA_H
