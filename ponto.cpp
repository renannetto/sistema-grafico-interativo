#include "ponto.h"

Ponto::Ponto(double vX, double vY){
    x = vX;
    y = vY;
}

Ponto::~Ponto(){
}

double Ponto::getX(){
    return x;
}

double Ponto::getY(){
    return y;
}
