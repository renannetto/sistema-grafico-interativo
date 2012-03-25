#include "displayfile.h"

DisplayFile::DisplayFile()
{
    nPontos = 0;
    nRetas = 0;
    nPoligonos = 0;

    list<Ponto*> pontosWindow;
    pontosWindow.push_back(new Ponto(0, 0));
    pontosWindow.push_back(new Ponto(640, 0));
    pontosWindow.push_back(new Ponto(640, 480));
    pontosWindow.push_back(new Ponto(0, 480));
    Cor preto(0, 0, 0);
    figuras.push_back(new Figura("Window", WINDOW, pontosWindow, preto));

    construirEixosNaOrigem();
}

DisplayFile::~ DisplayFile(){
}

void DisplayFile::construirEixosNaOrigem(){
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
    figuras.push_back(new Figura("Eixo X", EIXO, pontosEixoX, preto));
    figuras.push_back(new Figura("Eixo Y", EIXO, pontosEixoY, preto));
}

string DisplayFile::adicionarFigura(Tipo tipo, list<Ponto*> pontos, Cor cor)
{
    Figura *figura;
    string nome;
    stringstream nomeInt;
    switch(tipo)
    {
        case PONTO: nome = "Ponto";
                    nomeInt << nome << nPontos;
                    nome = nomeInt.str();
                    figura = new Figura(nome, tipo, pontos, cor);
                    nPontos++;
                    break;
        case RETA: nome = "Reta";
                   nomeInt << nome << nRetas;
                   nome = nomeInt.str();
                   figura = new Figura(nome, tipo, pontos, cor);
                   nRetas++;
                   break;
        case POLIGONO: nome = "Poligono";
                       nomeInt << nome << nPoligonos;
                       nome = nomeInt.str();
                       figura = new Figura(nome, tipo, pontos, cor);
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
