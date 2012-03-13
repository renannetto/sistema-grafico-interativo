#include "figura.h"

Figura::Figura(string vNome, Tipo vTipo, list<Ponto *> vPontos)
{
    nome = vNome;
    tipo = vTipo;
    pontos = vPontos;

    matrizT = new double*[3];
    for(int i = 0; i < 3; i++)
        matrizT[i] = new double[3];

    double xSum = 0, ySum = 0;
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        xSum += (*it)->obterX();
        ySum += (*it)->obterY();
    }
    xMedio = xSum/pontos.size();
    yMedio = ySum/pontos.size();
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
    matrizT[0][0] = 1; matrizT[0][1] = 0; matrizT[0][2] = 0;
    matrizT[1][0] = 0; matrizT[1][1] = 1; matrizT[1][2] = 0;
    matrizT[2][0] = vX; matrizT[2][1] = vY; matrizT[2][2] = 1;
    transformar2D();
}

void Figura::escalonar2D(double vX, double vY){
    matrizT[0][0] = vX; matrizT[0][1] = 0; matrizT[0][2] = 0;
    matrizT[1][0] = 0; matrizT[1][1] = vY; matrizT[1][2] = 0;
    matrizT[2][0] = xMedio*(1-vX); matrizT[2][1] = yMedio*(1-vY); matrizT[2][2] = 1;
    transformar2D();
}

void Figura::rotacionarNaOrigem2D(double teta){
    teta = teta*2*M_PI/360;
    matrizT[0][0] = cos(teta); matrizT[0][1] = -sin(teta); matrizT[0][2] = 0;
    matrizT[1][0] = sin(teta); matrizT[1][1] = cos(teta); matrizT[1][2] = 0;
    matrizT[2][0] = 0; matrizT[2][1] = 0; matrizT[2][2] = 1;
    transformar2D();
}

void Figura::rotacionarNoCentro2D(double teta){
    teta = teta*2*M_PI/360;
    matrizT[0][0] = cos(teta); matrizT[0][1] = -sin(teta); matrizT[0][2] = 0;
    matrizT[1][0] = sin(teta); matrizT[1][1] = cos(teta); matrizT[1][2] = 0;
    matrizT[2][0] = xMedio*(1-cos(teta)) - yMedio*sin(teta); matrizT[2][1] = yMedio*(1-cos(teta)) + xMedio*sin(teta); matrizT[2][2] = 1;
    transformar2D();
}

void Figura::rotacionarNoPonto2D(double teta, double pX, double pY){
    matrizT[0][0] = cos(teta); matrizT[0][1] = -sin(teta); matrizT[0][2] = 0;
    matrizT[1][0] = sin(teta); matrizT[1][1] = cos(teta); matrizT[1][2] = 0;
    matrizT[2][0] = pX*(1-cos(teta)) - pY*sin(teta); matrizT[2][1] = pY*(1-cos(teta)) + pX*sin(teta); matrizT[2][2] = 1;
    transformar2D();
}

void Figura::transformar2D(){
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        (*it)->transformar2D(matrizT);
    }
}
