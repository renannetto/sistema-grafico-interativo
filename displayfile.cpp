#include "displayfile.h"

DisplayFile::DisplayFile()
{
    nPontos = 0;
    nRetas = 0;
    nPoligonos = 0;

    list<Ponto*> pontosWindow;
    pontosWindow.push_back(new Ponto(-320, -240));
    pontosWindow.push_back(new Ponto(320, -240));
    pontosWindow.push_back(new Ponto(320, 240));
    pontosWindow.push_back(new Ponto(-320, 240));
    Cor preto(0, 0, 0);
    figuras.push_back(new Figura("Window", WINDOW, pontosWindow, preto, 0, 0, 0));

    construirEixosNaOrigem();
}

DisplayFile::~ DisplayFile(){
}

void DisplayFile::construirEixosNaOrigem(){
    Figura *window = figuras.front();
    Ponto centro = window->obterCentro();
    double wcX = centro.obterX();
    double wcY = centro.obterY();
    double teta = 0;

    list<Ponto*> pontosEixoX;
    list<Ponto*> pontosEixoY;
    pontosEixoX.push_back(new Ponto(0,0));
    pontosEixoX.push_back(new Ponto(130,0));
    pontosEixoX.push_back(new Ponto(110,6));
    pontosEixoX.push_back(new Ponto(130,0));
    pontosEixoX.push_back(new Ponto(110,-6));
    pontosEixoX.push_back(new Ponto(130,0));
    pontosEixoY.push_back(new Ponto(0,0));
    pontosEixoY.push_back(new Ponto(0,130));
    pontosEixoY.push_back(new Ponto(6,110));
    pontosEixoY.push_back(new Ponto(0,130));
    pontosEixoY.push_back(new Ponto(-6,110));
    pontosEixoY.push_back(new Ponto(0,130));
    Cor preto(0,0,0);
    figuras.push_back(new Figura("Eixo X", EIXO, pontosEixoX, preto, wcX, wcY, teta));
    figuras.push_back(new Figura("Eixo Y", EIXO, pontosEixoY, preto, wcX, wcY, teta));
}

string DisplayFile::adicionarFigura(Tipo tipo, list<Ponto*> pontos, Cor cor)
{
    Figura *window = figuras.front();
    Ponto centro = window->obterCentro();
    double wcX = centro.obterX();
    double wcY = centro.obterY();
    double teta = 0;

    Figura *figura;
    string nome;
    stringstream nomeInt;
    switch(tipo)
    {
        case PONTO: nome = "Ponto";
                    nomeInt << nome << nPontos;
                    nome = nomeInt.str();
                    figura = new Figura(nome, tipo, pontos, cor, wcX, wcY, teta);
                    nPontos++;
                    break;
        case RETA: nome = "Reta";
                   nomeInt << nome << nRetas;
                   nome = nomeInt.str();
                   figura = new Figura(nome, tipo, pontos, cor, wcX, wcY, teta);
                   nRetas++;
                   break;
        case POLIGONO: nome = "Poligono";
                       nomeInt << nome << nPoligonos;
                       nome = nomeInt.str();
                       figura = new Figura(nome, tipo, pontos, cor, wcX, wcY, teta);
                       nPoligonos++;
                       break;
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
