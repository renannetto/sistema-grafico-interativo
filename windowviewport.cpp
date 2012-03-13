#include "windowviewport.h"

WindowViewport::WindowViewport()
{
    displayFile = new DisplayFile();
    window = new Window();
}

WindowViewport::~WindowViewport(){
    delete window;
    delete displayFile;
}

string WindowViewport::adicionarFigura(Tipo tipo, list<Ponto*> pontos)
{
    return displayFile->adicionarFigura(tipo, pontos);
}

list<Figura*> WindowViewport::obterFiguras(){
    return displayFile->obterFiguras();
}

void WindowViewport::destruirFigura(string nome){
    displayFile->destruirFigura(nome);
}

void WindowViewport::zoomIn(int percent)
{
    window->zoomIn(percent);
}

void WindowViewport::zoomOut(int percent)
{
    window->zoomOut(percent);
}

void WindowViewport::moverParaEsquerda()
{
    window->moverParaEsquerda();
}

void WindowViewport::moverParaDireita()
{
    window->moverParaDireita();
}

void WindowViewport::moverParaBaixo()
{
    window->moverParaBaixo();
}

void WindowViewport::moverParaCima()
{
    window->moverParaCima();
}

double WindowViewport::fx(double x)
{
    return window->fx(x);
}

double WindowViewport::fy(double y)
{
    return window->fy(y);
}
