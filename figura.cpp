#include "figura.h"

Figura::Figura(string vNome, Tipo vTipo, list<Ponto *> vPontos)
{
    nome = vNome;
    tipo = vTipo;
    pontos = vPontos;
}

Figura::~Figura()
{
}

list<Ponto*> Figura::obterPontos(){
    return pontos;
}

string Figura::obterNome(){
    return nome;
}

Tipo Figura::obterTipo(){
    return tipo;
}

void Figura::transaladar2D(double vX, double vY) {
    double matriz[3][3] = {{1,0,0},{0,1,0},{vX,vY,1}};
    double** p = matriz;
    transformar2D(p);
}

void Figura::escalonar2D(double, double){

}

void Figura::rotacionarNaOrigem2D(double){

}

void Figura::rotacionarNoCentro2D(double){

}

void Figura::rotacionarNoPonto2D(double pX, double pY){

}

void Figura::transformar2D(double** matrizT){
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        (*it).transformar2D(matrizT);
    }
}
