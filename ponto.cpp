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

void Ponto::transformar2D(double** matrizT){
    double xN = x*matrizT[0][0] + y*matrizT[1][0] + matrizT[2][0];
    double yN = x*matrizT[0][1] + y*matrizT[1][1] + matrizT[2][1];
    x = xN;
    y = yN;
}
