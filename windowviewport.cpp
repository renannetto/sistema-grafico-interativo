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

void WindowViewport::resetarWindow(){
    window->resetarCoordenadas();
}

string WindowViewport::adicionarFigura(Tipo tipo, list<Ponto*> pontos, int vermelho, int verde, int azul)
{
    Cor cor = Cor(vermelho, verde, azul);
    return displayFile->adicionarFigura(tipo, pontos, cor);
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

double WindowViewport::obterXMinDaWindow(){
    return window->obterXMinDaWindow();
}

double WindowViewport::obterYMinDaWindow(){
    return window->obterYMinDaWindow();
}

double WindowViewport::obterXMaxDaWindow(){
    return window->obterXMaxDaWindow();
}

double WindowViewport::obterYMaxDaWindow(){
    return window->obterYMaxDaWindow();
}

void WindowViewport::transladar2D(string nomeFigura, double vX, double vY){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->transladar2D(vX,vY);
            break;
        }
    }
}

void WindowViewport::escalonar2D(string nomeFigura, double vX, double vY){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->escalonar2D(vX,vY);
            break;
        }
    }
}

void WindowViewport::rotacionarNaOrigem2D(string nomeFigura, double teta){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->rotacionarNaOrigem2D(teta);
            break;
        }
    }
}

void WindowViewport::rotacionarNoCentro2D(string nomeFigura, double teta){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->rotacionarNoCentro2D(teta);
            break;
        }
    }
}

void WindowViewport::rotacionarNoPonto2D(string nomeFigura, double teta, double pX, double pY){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->rotacionarNoPonto2D(teta,pX,pY);
            break;
        }
    }
}

void WindowViewport::mudarCor(string nomeFigura, int vermelho, int verde, int azul){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->mudarCor(vermelho, verde, azul);
            break;
        }
    }
}
