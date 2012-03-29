#ifndef WINDOWVIEWPORT_H
#define WINDOWVIEWPORT_H

#include "displayfile.h"
#include "window.h"
#include <string>
#include <limits>
#include <math.h>

#define PI 3.14159265;

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
    double obterXMinDaWindow(list<Ponto*> pontos);
    double obterYMinDaWindow(list<Ponto*> pontos);
    double obterXMaxDaWindow(list<Ponto*> pontos);
    double obterYMaxDaWindow(list<Ponto*> pontos);
    double obterXMinDaWindowMundo();
    double obterYMinDaWindowMundo();
    double obterXMaxDaWindowMundo();
    double obterYMaxDaWindowMundo();
    double obterXMinDaWindowPPC();
    double obterYMinDaWindowPPC();
    double obterXMaxDaWindowPPC();
    double obterYMaxDaWindowPPC();
    void transladar2D(string,double,double);
    void escalonar2D(string,double,double);
    void rotacionarNaOrigem2D(string,double);
    void rotacionarNoCentro2D(string,double);
    void rotacionarNoPonto2D(string,double,double,double);
    void mudarCor(string, int, int, int);
    void gerarDescricoesPPC();
private:
    DisplayFile *displayFile;
    Figura *window;
    double xMin;
    double xMax;
    double yMin;
    double yMax;
};

#endif // WINDOWVIEWPORT_H
