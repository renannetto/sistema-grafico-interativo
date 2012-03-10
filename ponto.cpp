#include "ponto.h"

Ponto::Ponto(double vX, double vY){
    x = vX;
    y = vY;
}

Ponto::~Ponto(){
}

void Ponto::setX(double newX){
    x = newX;
}

void Ponto::setY(double newY){
    y = newY;
}
