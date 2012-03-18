#ifndef WINDOWVIEWPORT_H
#define WINDOWVIEWPORT_H

#include "displayfile.h"
#include "window.h"
#include <string>

class WindowViewport
{
public:
    WindowViewport();
    ~WindowViewport();
    string adicionarFigura(Tipo tipo, list<Ponto*> pontos, int vermelho, int verde, int azul);
    list<Figura*> obterFiguras();
    void resetarWindow();
    void destruirFigura(string);
    void zoomIn(int);
    void zoomOut(int);
    void moverParaEsquerda();
    void moverParaDireita();
    void moverParaCima();
    void moverParaBaixo();
    double fx(double x);
    double fy(double y);
    void transladar2D(string,double,double);
    void escalonar2D(string,double,double);
    void rotacionarNaOrigem2D(string,double);
    void rotacionarNoCentro2D(string,double);
    void rotacionarNoPonto2D(string,double,double,double);
    void mudarCor(string, int, int, int);
private:
    DisplayFile *displayFile;
    Window *window;
};

#endif // WINDOWVIEWPORT_H
