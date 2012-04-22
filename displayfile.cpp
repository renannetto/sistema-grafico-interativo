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
    list<Face*> faces;
    Ponto vrp(pontosWindow.front()->obterX(), pontosWindow.front()->obterY(), pontosWindow.front()->obterZ());
    Figura* window = new Figura("Window", WINDOW, pontosWindow, faces, preto, vrp, 0, 0, 0, 0, 0, 0);
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
    list<Face*> faces;
    figuras.push_back(new Figura("Eixo X", EIXO, pontosEixoX, faces, preto, vrp, tetaX, tetaY, wcX, wcY, wcZ, teta));
    figuras.push_back(new Figura("Eixo Y", EIXO, pontosEixoY, faces, preto, vrp, tetaX, tetaY, wcX, wcY, wcZ, teta));


    //Teste poliedro
    list<Ponto*> pontosPoliedro;
    Ponto *ponto1 = new Ponto(0, 0, 0);
    Ponto *ponto2 = new Ponto(50, 0, 0);
    Ponto *ponto3 = new Ponto(50, 50, 0);
    Ponto *ponto4 = new Ponto(0, 50, 0);
    Ponto *ponto5 = new Ponto(10, 10, -50);
    Ponto *ponto6 = new Ponto(60, 10, -50);
    Ponto *ponto7 = new Ponto(60, 60, -50);
    Ponto *ponto8 = new Ponto(10, 60, -50);
    pontosPoliedro.push_back(ponto1);
    pontosPoliedro.push_back(ponto2);
    pontosPoliedro.push_back(ponto3);
    pontosPoliedro.push_back(ponto4);
    pontosPoliedro.push_back(ponto5);
    pontosPoliedro.push_back(ponto6);
    pontosPoliedro.push_back(ponto7);
    pontosPoliedro.push_back(ponto8);
    list<Face*> facesPoliedro;
    facesPoliedro.push_back(new Face(1, 2, 3));
    facesPoliedro.push_back(new Face(4, 1, 3));
    facesPoliedro.push_back(new Face(1, 5, 8));
    facesPoliedro.push_back(new Face(4, 1, 8));
    facesPoliedro.push_back(new Face(2, 6, 7));
    facesPoliedro.push_back(new Face(3, 2, 7));
    facesPoliedro.push_back(new Face(5, 6, 7));
    facesPoliedro.push_back(new Face(8, 5, 6));
    figuras.push_back(new Figura("Poliedro", POLIEDRO, pontosPoliedro, facesPoliedro, preto, vrp, tetaX, tetaY, wcX, wcY, wcZ, teta));

}

string DisplayFile::adicionarFigura(Tipo tipo, list<Ponto*> pontos, list<Face*> faces, Cor cor)
{
    Figura *window = figuras.front();

    list<Ponto*> pontosWindow = window->obterPontos();
    Ponto vrp(pontosWindow.front()->obterX(), pontosWindow.front()->obterY(), pontosWindow.front()->obterZ());
    //Ponto vrp(-320, -240, 0);

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
        figura = new Figura(nome, tipo, pontos, faces, cor, vrp, tetaX, tetaY, wcX, wcY, wcZ, teta);
        nPontos++;
        break;
    case RETA:
        nome = "Reta ";
        nomeInt << nome << nRetas;
        nome = nomeInt.str();
        figura = new Figura(nome, tipo, pontos, faces, cor, vrp, tetaX, tetaY, wcX, wcY, wcZ, teta);
        nRetas++;
        break;
    case POLIGONO:
        nome = "Poligono ";
        nomeInt << nome << nPoligonos;
        nome = nomeInt.str();
        figura = new Figura(nome, tipo, pontos, faces, cor, vrp, tetaX, tetaY, wcX, wcY, wcZ, teta);
        nPoligonos++;
        break;
    case POLIGONOPREENCHIDO:
        nome = "Poligono Preenchido ";
        nomeInt << nome << nPoligonosP;
        nome = nomeInt.str();
        figura = new Figura(nome, tipo, pontos, faces, cor, vrp, tetaX, tetaY, wcX, wcY, wcZ, teta);
        nPoligonosP++;
        break;
    case CURVABEZIER :
        nome = "Bezier ";
        nomeInt << nome << nBeziers;
        nome = nomeInt.str();
        figura = new Figura(nome, tipo, pontos, faces, cor, vrp, tetaX, tetaY, wcX, wcY, wcZ, teta);
        nBeziers++;
        break;
    case CURVASPLINE :
        nome = "Spline ";
        nomeInt << nome << nSplines;
        nome = nomeInt.str();
        figura = new Figura(nome, tipo, pontos, faces, cor, vrp, tetaX, tetaY, wcX, wcY, wcZ, teta);
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
