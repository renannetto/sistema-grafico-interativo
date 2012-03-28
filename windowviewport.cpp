#include "windowviewport.h"

WindowViewport::WindowViewport()
{
    displayFile = new DisplayFile();
    window = displayFile->obterFiguras().front();
}

WindowViewport::~WindowViewport(){
    delete window;
    delete displayFile;
}

void WindowViewport::resetarWindow(){
    delete(window);
    list<Ponto*> pontosWindow;
    pontosWindow.push_back(new Ponto(-320, -240));
    pontosWindow.push_back(new Ponto(320, -240));
    pontosWindow.push_back(new Ponto(320, 240));
    pontosWindow.push_back(new Ponto(-320, 240));
    Cor preto(0, 0, 0);
    window = new Figura("Window", WINDOW, pontosWindow, preto, 0, 0, 0);
    gerarDescricoesPPC();
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
    window->escalonar2D(1+(double)percent/100, 1+(double)percent/100);
}

void WindowViewport::zoomOut(int percent)
{
    window->escalonar2D((double)100/(percent+100), (double)100/(percent+100));
}

void WindowViewport::moverParaEsquerda()
{
    window->transladar2D(-0.1*(obterXMaxDaWindow()-obterXMinDaWindow()), 0);
}

void WindowViewport::moverParaDireita()
{
    window->transladar2D(0.1*(obterXMaxDaWindow()-obterXMinDaWindow()), 0);
}

void WindowViewport::moverParaBaixo()
{
    window->transladar2D(0, -0.1*(obterYMaxDaWindow()-obterYMinDaWindow()));
}

void WindowViewport::moverParaCima()
{
    window->transladar2D(0, 0.1*(obterYMaxDaWindow()-obterYMinDaWindow()));
}

double WindowViewport::obterXMinDaWindow(){
    list<Ponto*> pontos = window->obterPontosPPC();
    double xMin = 510515250;
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        if ((*it)->obterX() < xMin){
            xMin = (*it)->obterX();
        }
    }
    return xMin;
}

double WindowViewport::obterYMinDaWindow(){
    list<Ponto*> pontos = window->obterPontosPPC();
    double yMin = 510515250;
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        if ((*it)->obterY() < yMin){
            yMin = (*it)->obterY();
        }
    }
    return yMin;
}

double WindowViewport::obterXMaxDaWindow(){
    list<Ponto*> pontos = window->obterPontosPPC();
    double xMax = -510515250;
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        if ((*it)->obterX() > xMax){
            xMax = (*it)->obterX();
        }
    }
    return xMax;
}

double WindowViewport::obterYMaxDaWindow(){
    list<Ponto*> pontos = window->obterPontosPPC();
    double yMax = -510515250;
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        if ((*it)->obterY() > yMax){
            yMax = (*it)->obterY();
        }
    }
    return yMax;
}

double WindowViewport::obterXMinOriginalDaWindow(){
    list<Ponto*> pontos = window->obterPontos();
    double xMin = numeric_limits<double>::max();
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        if ((*it)->obterX() < xMin){
            xMin = (*it)->obterX();
        }
    }
    return xMin;
}

double WindowViewport::obterYMinOriginalDaWindow(){
    list<Ponto*> pontos = window->obterPontosPPC();
    double yMin = numeric_limits<double>::max();
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        if ((*it)->obterY() < yMin){
            yMin = (*it)->obterY();
        }
    }
    return yMin;
}

double WindowViewport::obterXMaxOriginalDaWindow(){
    list<Ponto*> pontos = window->obterPontos();
    double xMax = numeric_limits<double>::min();
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        if ((*it)->obterX() > xMax){
            xMax = (*it)->obterX();
        }
    }
    return xMax;
}

double WindowViewport::obterYMaxOriginalDaWindow(){
    list<Ponto*> pontos = window->obterPontos();
    double yMax = numeric_limits<double>::min();
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        if ((*it)->obterY() > yMax){
            yMax = (*it)->obterY();
        }
    }
    return yMax;
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

void WindowViewport::gerarDescricoesPPC(){
    Ponto centro = window->obterCentro();
    double wcX = centro.obterX();
    double wcY = centro.obterY();
    double teta = 0;

    list<Figura*> figuras = displayFile->obterFiguras();
    /*figuras.pop_front();
    for(int i=0; i<figuras.size(); i++) {
        Figura *figura = figuras.front();
        figuras.pop_front();
        figura->gerarDescricaoPPC(wcX, wcY, teta);
        figuras.push_back(figura);
    }
    figuras.push_back(window);*/

    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        (*it)->gerarDescricaoPPC(wcX, wcY, teta);
    }
}
