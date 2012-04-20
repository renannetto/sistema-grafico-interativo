#include "displayfile.h"

DisplayFile::DisplayFile()
{
    nPontos = 0;
    nRetas = 0;
    nPoligonos = 0;
    nPoligonosP = 0;
    nBeziers = 0;
    nSplines = 0;

    window = criarWindow();
    figuras.push_back(window);

    construirEixosNaOrigem();
}

DisplayFile::~ DisplayFile(){
}

Figura* DisplayFile::criarWindow(){
    list<Ponto*> pontosWindow;
    pontosWindow.push_back(new Ponto(-320, -240));
    pontosWindow.push_back(new Ponto(320, -240));
    pontosWindow.push_back(new Ponto(320, 240));
    pontosWindow.push_back(new Ponto(-320, 240));
    Cor preto(0, 0, 0);
    Ponto vrp(pontosWindow.front()->obterX(), pontosWindow.front()->obterY(), pontosWindow.front()->obterZ());
    Figura* window = new Figura("Window", WINDOW, pontosWindow, preto, vrp, 0, 0, 0, 0, 0, 0);
    return window;
}

void DisplayFile::construirEixosNaOrigem(){
    Figura *window = figuras.front();

    list<Ponto*> pontosWindow = window->obterPontos();
    Ponto vrp(pontosWindow.front()->obterX(), pontosWindow.front()->obterY(), pontosWindow.front()->obterZ());

    double tetaX = 0;
    double tetaY = 0;

    Ponto centro = window->obterCentro();
    double wcX = centro.obterX();
    double wcY = centro.obterY();
    double wcZ = centro.obterZ();
    double teta = 0;

    list<Ponto*> pontosEixoX;
    list<Ponto*> pontosEixoY;
    pontosEixoX.push_back(new Ponto(-120,0));
    pontosEixoX.push_back(new Ponto(120,0));
    pontosEixoX.push_back(new Ponto(110,4));
    pontosEixoX.push_back(new Ponto(120,0));
    pontosEixoX.push_back(new Ponto(110,-4));
    pontosEixoX.push_back(new Ponto(120,0));
    pontosEixoY.push_back(new Ponto(0,-120));
    pontosEixoY.push_back(new Ponto(0,120));
    pontosEixoY.push_back(new Ponto(4,110));
    pontosEixoY.push_back(new Ponto(0,120));
    pontosEixoY.push_back(new Ponto(-4,110));
    pontosEixoY.push_back(new Ponto(0,120));
    Cor preto(0,0,0);
    figuras.push_back(new Figura("Eixo X", EIXO, pontosEixoX, preto, vrp, tetaX, tetaY, wcX, wcY, wcZ, teta));
    figuras.push_back(new Figura("Eixo Y", EIXO, pontosEixoY, preto, vrp, tetaX, tetaY, wcX, wcY, wcZ, teta));
}

string DisplayFile::adicionarFigura(Tipo tipo, list<Ponto*> pontos, Cor cor)
{
    Figura *window = figuras.front();

    list<Ponto*> pontosWindow = window->obterPontos();
    Ponto vrp(pontosWindow.front()->obterX(), pontosWindow.front()->obterY(), pontosWindow.front()->obterZ());

    double tetaX = 0;
    double tetaY = 0;

    Ponto centro = window->obterCentro();
    double wcX = centro.obterX();
    double wcY = centro.obterY();
    double wcZ = centro.obterZ();

    double teta = obterAnguloDaWindow();

    Figura *figura;
    string nome;
    stringstream nomeInt;
    switch(tipo)
    {
    case PONTO:
        nome = "Ponto ";
        nomeInt << nome << nPontos;
        nome = nomeInt.str();
        figura = new Figura(nome, tipo, pontos, cor, vrp, tetaX, tetaY, wcX, wcY, wcZ, teta);
        nPontos++;
        break;
    case RETA:
        nome = "Reta ";
        nomeInt << nome << nRetas;
        nome = nomeInt.str();
        figura = new Figura(nome, tipo, pontos, cor, vrp, tetaX, tetaY, wcX, wcY, wcZ, teta);
        nRetas++;
        break;
    case POLIGONO:
        nome = "Poligono ";
        nomeInt << nome << nPoligonos;
        nome = nomeInt.str();
        figura = new Figura(nome, tipo, pontos, cor, vrp, tetaX, tetaY, wcX, wcY, wcZ, teta);
        nPoligonos++;
        break;
    case POLIGONOPREENCHIDO:
        nome = "Poligono Preenchido ";
        nomeInt << nome << nPoligonosP;
        nome = nomeInt.str();
        figura = new Figura(nome, tipo, pontos, cor, vrp, tetaX, tetaY, wcX, wcY, wcZ, teta);
        nPoligonosP++;
        break;
    case CURVABEZIER :
        nome = "Bezier ";
        nomeInt << nome << nBeziers;
        nome = nomeInt.str();
        figura = new Figura(nome, tipo, pontos, cor, vrp, tetaX, tetaY, wcX, wcY, wcZ, teta);
        nBeziers++;
        break;
    case CURVASPLINE :
        nome = "Spline ";
        nomeInt << nome << nSplines;
        nome = nomeInt.str();
        figura = new Figura(nome, tipo, pontos, cor, vrp, tetaX, tetaY, wcX, wcY, wcZ, teta);
        nSplines++;
        break;
    case EIXO: break;
    case WINDOW: break;
    }
    figuras.push_back(figura);
    return nome;
}

list<Figura*> DisplayFile::obterFiguras(){
    return figuras;
}

void DisplayFile::destruirFigura(string nome){
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nome){
            figuras.erase(it);
            break;
        }
    }
}

double DisplayFile::obterAnguloDaWindow()
{
    list<Ponto*> pontosWindow = window->obterPontos();
    Ponto* pontoInicial = pontosWindow.front();
    Ponto* pontoFinal = pontosWindow.back();
    Ponto* vetor = new Ponto(pontoFinal->obterX()-pontoInicial->obterX(), pontoFinal->obterY()-pontoInicial->obterY());

    double x = vetor->obterX();
    double y = vetor->obterY();

    double teta = acos(y/sqrt(x*x+y*y));
    teta = (teta*180)/PI;

    if (pontoInicial->obterX()>pontoFinal->obterX())
        teta = 360 - teta;

    return teta;
}
