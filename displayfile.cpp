#include "displayfile.h"
#include <stdio.h>

DisplayFile::DisplayFile()
{
    nPontos = 0;
    nRetas = 0;
    nPoligonos = 0;
    nPoligonosP = 0;
    nBeziers = 0;
    nSplines = 0;
    nPoliedros = 0;

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
    Figura* window = new Figura("Window", WINDOW, pontosWindow, faces, preto, vrp, 0, 0, Ponto(0,0,0), 0);
    return window;
}

void DisplayFile::construirEixosNaOrigem(){
    Figura *window = figuras.front();

    list<Ponto*> pontosWindow = window->obterPontos();
    //Ponto vrp(pontosWindow.front()->obterX(), pontosWindow.front()->obterY(), pontosWindow.front()->obterZ());
    Ponto vrp(0,0,0);

    Ponto *ponto1Window = pontosWindow.front();
    Ponto *ponto4Window = pontosWindow.back();
    pontosWindow.pop_front();
    Ponto *ponto2Window = pontosWindow.front();
    pontosWindow.push_front(ponto1Window);

    Ponto vetor1(ponto2Window->obterX()-ponto1Window->obterX(), ponto2Window->obterY()-ponto1Window->obterY(), ponto2Window->obterZ()-ponto1Window->obterZ());
    Ponto vetor2(ponto4Window->obterX()-ponto1Window->obterX(), ponto4Window->obterY()-ponto1Window->obterY(), ponto4Window->obterZ()-ponto1Window->obterZ());

    double xOrtogonal = vetor1.obterY()*vetor2.obterZ() - vetor1.obterZ()*vetor2.obterY();
    double yOrtogonal = vetor1.obterZ()*vetor2.obterX() - vetor1.obterX()*vetor2.obterZ();
    double zOrtogonal = vetor1.obterX()*vetor2.obterY() - vetor1.obterY()*vetor2.obterX();

    Ponto centro = window->obterCentro();

    double moduloVnp = sqrt(xOrtogonal*xOrtogonal + yOrtogonal*yOrtogonal + zOrtogonal*zOrtogonal);
    double tetaX = acos(xOrtogonal/moduloVnp);
    double tetaY = acos(yOrtogonal/moduloVnp);
    //TODO
    //AQUI FOI ALTERADO PARA ASIN, NAO TENHO CERTEZA SE ESTA CERTO!!!

    if(zOrtogonal > 0)
        tetaX = 2*M_PI - tetaX;
    if(xOrtogonal < 0)
        tetaY = 2*M_PI - tetaY;

    double teta = 0;

    list<Ponto*> pontosEixoXPreto;
    list<Ponto*> pontosEixoXCinza;
    list<Ponto*> pontosEixoYPreto;
    list<Ponto*> pontosEixoYCinza;
    list<Ponto*> pontosEixoZPreto;
    list<Ponto*> pontosEixoZCinza;
    pontosEixoXPreto.push_back(new Ponto(0,0,0));
    pontosEixoXPreto.push_back(new Ponto(120,0,0));
    pontosEixoXCinza.push_back(new Ponto(0,0,0));
    pontosEixoXCinza.push_back(new Ponto(-120,0,0));
    pontosEixoYPreto.push_back(new Ponto(0,0,0));
    pontosEixoYPreto.push_back(new Ponto(0,120,0));
    pontosEixoYCinza.push_back(new Ponto(0,0,0));
    pontosEixoYCinza.push_back(new Ponto(0,-120,0));
    pontosEixoZPreto.push_back(new Ponto(0,0,0));
    pontosEixoZPreto.push_back(new Ponto(0,0,120));
    pontosEixoZCinza.push_back(new Ponto(0,0,0));
    pontosEixoZCinza.push_back(new Ponto(0,0,-120));
    Cor preto(0,0,0);
    Cor cinza(160,160,160);
    list<Face*> faces;
    figuras.push_back(new Figura("Eixo X Preto", EIXO, pontosEixoXPreto, faces, preto, vrp, tetaX, tetaY, centro, teta));
    figuras.push_back(new Figura("Eixo Y Preto", EIXO, pontosEixoYPreto, faces, preto, vrp, tetaX, tetaY, centro, teta));
    figuras.push_back(new Figura("Eixo Z Preto", EIXO, pontosEixoZPreto, faces, preto, vrp, tetaX, tetaY, centro, teta));
    figuras.push_back(new Figura("Eixo Y Cinza", EIXO, pontosEixoXCinza, faces, cinza, vrp, tetaX, tetaY, centro, teta));
    figuras.push_back(new Figura("Eixo X Cinza", EIXO, pontosEixoYCinza, faces, cinza, vrp, tetaX, tetaY, centro, teta));
    figuras.push_back(new Figura("Eixo Z Cinza", EIXO, pontosEixoZCinza, faces, cinza, vrp, tetaX, tetaY, centro, teta));


    //Teste poliedro
    list<Ponto*> pontosPoliedro;
    Ponto *ponto1 = new Ponto(5, 5, 5);
    Ponto *ponto2 = new Ponto(50, 5, 5);
    Ponto *ponto3 = new Ponto(50, 50, 5);
    Ponto *ponto4 = new Ponto(5, 50, 5);
    Ponto *ponto5 = new Ponto(5, 5, -50);
    Ponto *ponto6 = new Ponto(50, 5, -50);
    Ponto *ponto7 = new Ponto(50, 50, -50);
    Ponto *ponto8 = new Ponto(5, 50, -50);
    pontosPoliedro.push_back(ponto1);
    pontosPoliedro.push_back(ponto2);
    pontosPoliedro.push_back(ponto3);
    pontosPoliedro.push_back(ponto4);
    pontosPoliedro.push_back(ponto5);
    pontosPoliedro.push_back(ponto6);
    pontosPoliedro.push_back(ponto7);
    pontosPoliedro.push_back(ponto8);
    list<Face*> facesPoliedro;

    facesPoliedro.push_back(new Face(4, 1, 3));
    facesPoliedro.push_back(new Face(3, 4, 8));
    facesPoliedro.push_back(new Face(4, 1, 8));
    facesPoliedro.push_back(new Face(2, 6, 5));
    facesPoliedro.push_back(new Face(6, 2, 7));
    facesPoliedro.push_back(new Face(1, 2, 3));
    facesPoliedro.push_back(new Face(6, 7, 8));
    facesPoliedro.push_back(new Face(1, 5, 8));

    adicionarFigura(POLIEDRO, pontosPoliedro, facesPoliedro, preto);

}

string DisplayFile::adicionarFigura(Tipo tipo, list<Ponto*> pontos, list<Face*> faces, Cor cor)
{
    Figura *window = figuras.front();

    list<Ponto*> pontosWindow = window->obterPontos();
    Ponto vrp(pontosWindow.front()->obterX(), pontosWindow.front()->obterY(), pontosWindow.front()->obterZ());
    //Ponto vrp(-320, -240, 0);

    Ponto *ponto1Window = pontosWindow.front();
    Ponto *ponto4Window = pontosWindow.back();
    pontosWindow.pop_front();
    Ponto *ponto2Window = pontosWindow.front();
    pontosWindow.push_front(ponto1Window);

    Ponto vetor1(ponto2Window->obterX()-ponto1Window->obterX(), ponto2Window->obterY()-ponto1Window->obterY(), ponto2Window->obterZ()-ponto1Window->obterZ());
    Ponto vetor2(ponto4Window->obterX()-ponto1Window->obterX(), ponto4Window->obterY()-ponto1Window->obterY(), ponto4Window->obterZ()-ponto1Window->obterZ());

    double xOrtogonal = vetor1.obterY()*vetor2.obterZ() - vetor1.obterZ()*vetor2.obterY();
    double yOrtogonal = vetor1.obterZ()*vetor2.obterX() - vetor1.obterX()*vetor2.obterZ();
    double zOrtogonal = vetor1.obterX()*vetor2.obterY() - vetor1.obterY()*vetor2.obterX();

    double moduloVnp = sqrt(xOrtogonal*xOrtogonal + yOrtogonal*yOrtogonal + zOrtogonal*zOrtogonal);
    double tetaX = acos(xOrtogonal/moduloVnp);
    double tetaY = acos(yOrtogonal/moduloVnp);
    //TODO
    //AQUI FOI ALTERADO PARA ASIN, NAO TENHO CERTEZA SE ESTA CERTO!!!

    if(zOrtogonal > 0)
        tetaX = 2*M_PI - tetaX;
    if(xOrtogonal < 0)
        tetaY = 2*M_PI - tetaY;

    Ponto centro = window->obterCentro();

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
        figura = new Figura(nome, tipo, pontos, faces, cor, vrp, tetaX, tetaY, centro, teta);
        nPontos++;
        break;
    case RETA:
        nome = "Reta ";
        nomeInt << nome << nRetas;
        nome = nomeInt.str();
        figura = new Figura(nome, tipo, pontos, faces, cor, vrp, tetaX, tetaY, centro, teta);
        nRetas++;
        break;
    case POLIGONO:
        nome = "Poligono ";
        nomeInt << nome << nPoligonos;
        nome = nomeInt.str();
        figura = new Figura(nome, tipo, pontos, faces, cor, vrp, tetaX, tetaY, centro, teta);
        nPoligonos++;
        break;
    case POLIGONOPREENCHIDO:
        nome = "Poligono Preenchido ";
        nomeInt << nome << nPoligonosP;
        nome = nomeInt.str();
        figura = new Figura(nome, tipo, pontos, faces, cor, vrp, tetaX, tetaY, centro, teta);
        nPoligonosP++;
        break;
    case CURVABEZIER :
        nome = "Bezier ";
        nomeInt << nome << nBeziers;
        nome = nomeInt.str();
        figura = new Figura(nome, tipo, pontos, faces, cor, vrp, tetaX, tetaY, centro, teta);
        nBeziers++;
        break;
    case CURVASPLINE :
        nome = "Spline ";
        nomeInt << nome << nSplines;
        nome = nomeInt.str();
        figura = new Figura(nome, tipo, pontos, faces, cor, vrp, tetaX, tetaY, centro, teta);
        nSplines++;
        break;
    case POLIEDRO :
        nome = "Poliedro ";
        nomeInt << nome << nPoliedros;
        nome = nomeInt.str();
        figura = new Figura(nome, tipo, pontos, faces, cor, vrp, tetaX, tetaY, centro, teta);
        nPoliedros++;
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
    list<Ponto*> pontosWindow = window->obterPontosPPC();
    Ponto* pontoInicial = pontosWindow.front();
    Ponto* pontoFinal = pontosWindow.back();
    Ponto* vetor = new Ponto(pontoFinal->obterX()-pontoInicial->obterX(), pontoFinal->obterY()-pontoInicial->obterY());

    double x = vetor->obterX();
    double y = vetor->obterY();

    double teta = acos(y/sqrt(x*x+y*y));
    teta = (teta*180)/PI;

    if (pontoInicial->obterX()<pontoFinal->obterX())
        teta = 360 - teta;

    return teta;
}
