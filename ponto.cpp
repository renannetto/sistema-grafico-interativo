#include "ponto.h"

Ponto::Ponto(double vX, double vY){
    x = vX;
    y = vY;
}

Ponto::~Ponto(){
}

double Ponto::obterX() const{
    return x;
}

double Ponto::obterY() const{
    return y;
}

void Ponto::transformar2D(double** matrizT){
    double xN = x*matrizT[0][0] + y*matrizT[1][0] + matrizT[2][0];
    double yN = x*matrizT[0][1] + y*matrizT[1][1] + matrizT[2][1];
    x = xN;
    y = yN;
}

void Ponto::setarX(double nx){
    x = nx;
}

void Ponto::setarY(double ny){
    y = ny;
}

bool Ponto::operator ==(Ponto ponto){
    return (this->x == ponto.obterX() && this->y == ponto.obterY());
}
