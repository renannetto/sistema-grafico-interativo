#include "windowviewport.h"
#include <stdio.h>

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
    window = displayFile->criarWindow();
    gerarDescricoesPPC();
}

string WindowViewport::adicionarFigura(Tipo tipo, list<Ponto*> pontos, list<Face*> faces, int vermelho, int verde, int azul)
{
    Cor cor = Cor(vermelho, verde, azul);
    return displayFile->adicionarFigura(tipo, pontos, faces, cor);
}

list<Figura*> WindowViewport::obterFiguras(){
    return displayFile->obterFiguras();
}

void WindowViewport::destruirFigura(string nome){
    displayFile->destruirFigura(nome);
}

void WindowViewport::zoomIn(int percent)
{
    window->escalonar(1-(double)percent/100, 1-(double)percent/100);
    //window->escalonar2D((double)100/(percent+100), (double)100/(percent+100));
}

void WindowViewport::zoomOut(int percent)
{
    window->escalonar((double)100/(100-percent), (double)100/(100-percent));
    //window->escalonar2D(1+(double)percent/100, 1+(double)percent/100);
}

void WindowViewport::moverParaEsquerda()
{
    double teta = obterAnguloDaWindow();
    teta = (teta+270)*M_PI/180;
    double modulo = 0.1*(obterXMaxDaWindowPPC()-obterXMinDaWindowPPC());
    double vY = modulo*cos(teta);
    double vX = modulo*sin(teta);
    window->transladar(vX, vY);
}

void WindowViewport::moverParaDireita()
{
    double teta = obterAnguloDaWindow();
    teta = (teta+90)*M_PI/180;
    double modulo = 0.1*(obterXMaxDaWindowPPC()-obterXMinDaWindowPPC());
    double vY = modulo*cos(teta);
    double vX = modulo*sin(teta);
    window->transladar(vX, vY);
}

void WindowViewport::moverParaBaixo()
{
    double teta = obterAnguloDaWindow();
    teta = (teta+180)*M_PI/180;
    double modulo = 0.1*(obterYMaxDaWindowPPC()-obterYMinDaWindowPPC());
    double vY = modulo*cos(teta);
    double vX = modulo*sin(teta);
    window->transladar(vX, vY);
}

void WindowViewport::moverParaCima()
{
    double teta = obterAnguloDaWindow();
    teta = teta*M_PI/180;
    double modulo = 0.1*(obterYMaxDaWindowPPC()-obterYMinDaWindowPPC());
    double vY = modulo*cos(teta);
    double vX = modulo*sin(teta);
    window->transladar(vX, vY);
}

double WindowViewport::obterXMinDaWindow(list<Ponto*> pontos){
    double xMin = numeric_limits<double>::max();
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        if ((*it)->obterX() < xMin){
            xMin = (*it)->obterX();
        }
    }
    return xMin;
}

double WindowViewport::obterYMinDaWindow(list<Ponto*> pontos){
    double yMin = numeric_limits<double>::max();
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        if ((*it)->obterY() < yMin){
            yMin = (*it)->obterY();
        }
    }
    return yMin;
}

double WindowViewport::obterXMaxDaWindow(list<Ponto*> pontos){
    double xMax = numeric_limits<double>::min();
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        if ((*it)->obterX() > xMax){
            xMax = (*it)->obterX();
        }
    }
    return xMax;
}

double WindowViewport::obterYMaxDaWindow(list<Ponto*> pontos){
    double yMax = numeric_limits<double>::min();
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        if ((*it)->obterY() > yMax){
            yMax = (*it)->obterY();
        }
    }
    return yMax;
}

double WindowViewport::obterXMaxDaWindowMundo(){
    list<Ponto*> pontos = window->obterPontos();
    return obterXMaxDaWindow(pontos);
}

double WindowViewport::obterXMinDaWindowMundo(){
    list<Ponto*> pontos = window->obterPontos();
    return obterXMinDaWindow(pontos);
}

double WindowViewport::obterYMaxDaWindowMundo(){
    list<Ponto*> pontos = window->obterPontos();
    return obterYMaxDaWindow(pontos);
}

double WindowViewport::obterYMinDaWindowMundo(){
    list<Ponto*> pontos = window->obterPontos();
    return obterYMinDaWindow(pontos);
}

double WindowViewport::obterXMaxDaWindowPPC(){
    list<Ponto*> pontos = window->obterPontosPPC();
    return obterXMaxDaWindow(pontos);
}

double WindowViewport::obterXMinDaWindowPPC(){
    list<Ponto*> pontos = window->obterPontosPPC();
    return obterXMinDaWindow(pontos);
}

double WindowViewport::obterYMaxDaWindowPPC(){
    list<Ponto*> pontos = window->obterPontosPPC();
    return obterYMaxDaWindow(pontos);
}

double WindowViewport::obterYMinDaWindowPPC(){
    list<Ponto*> pontos = window->obterPontosPPC();
    return obterYMinDaWindow(pontos);
}

double WindowViewport::obterCentroXDaWindow(){
    return window->obterCentro().obterX();
}

double WindowViewport::obterCentroYDaWindow(){
    return window->obterCentro().obterY();
}

void WindowViewport::transladar(string nomeFigura, double vX, double vY){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->transladar(vX,vY);
            break;
        }
    }
}

void WindowViewport::escalonar(string nomeFigura, double vX, double vY){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->escalonar(vX,vY);
            break;
        }
    }
}

void WindowViewport::rotacionarNaOrigem(string nomeFigura, double teta, Ponto vetor){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->rotacionarNaOrigem(teta, vetor);
            break;
        }
    }
}

void WindowViewport::rotacionarNoCentro(string nomeFigura, double teta, Ponto vetor){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->rotacionarNoCentro(teta, vetor);
            break;
        }
    }
}

void WindowViewport::rotacionarNoPonto(string nomeFigura, double teta, double pX, double pY, double pZ, Ponto vetor){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->rotacionarNoPonto(teta,pX,pY, pZ, vetor);
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
    list<Ponto*> pontosWindow = window->obterPontos();
    Ponto *ponto1Window = pontosWindow.front();
    Ponto *ponto4Window = pontosWindow.back();
    pontosWindow.pop_front();
    Ponto *ponto2Window = pontosWindow.front();
    pontosWindow.push_front(ponto1Window);

    Ponto vetor1(ponto2Window->obterX()-ponto1Window->obterX(), ponto2Window->obterY()-ponto1Window->obterY());
    Ponto vetor2(ponto4Window->obterX()-ponto1Window->obterX(), ponto4Window->obterY()-ponto1Window->obterY());

    double xOrtogonal = vetor1.obterY()*vetor2.obterZ() - vetor1.obterZ()*vetor2.obterY();
    double yOrtogonal = vetor1.obterZ()*vetor2.obterX() - vetor1.obterX()*vetor2.obterZ();
    double zOrtogonal = vetor1.obterX()*vetor2.obterY() - vetor1.obterY()*vetor2.obterX();

    double moduloVnp = sqrt(xOrtogonal*xOrtogonal + yOrtogonal*yOrtogonal + zOrtogonal*zOrtogonal);
    double tetaX = asin(xOrtogonal/moduloVnp);
    double tetaY = asin(yOrtogonal/moduloVnp);
    //TODO
    //AQUI FOI ALTERADO PARA ASIN, NAO TENHO CERTEZA SE ESTA CERTO!!!

    Ponto vrp(pontosWindow.front()->obterX(), pontosWindow.front()->obterY(), pontosWindow.front()->obterZ());

    Ponto centro = window->obterCentro();
    double wcX = centro.obterX();
    double wcY = centro.obterY();
    double wcZ = centro.obterZ();

    double teta = obterAnguloDaWindow();

    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        (*it)->gerarDescricaoPPC(vrp, tetaX, tetaY, wcX, wcY, wcZ, teta);
    }
}

double WindowViewport::obterAnguloDaWindow()
{
    return displayFile->obterAnguloDaWindow();
}
