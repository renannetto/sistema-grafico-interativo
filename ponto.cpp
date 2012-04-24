#include "ponto.h"

Ponto::Ponto(double vX, double vY, double vZ){
    x = vX;
    y = vY;
    z = vZ;
}

Ponto::~Ponto(){
}

double Ponto::obterX() const{
    return x;
}

double Ponto::obterY() const{
    return y;
}

double Ponto::obterZ() const{
    return z;
}

void Ponto::transformar(double** matrizT){
    double xN = x*matrizT[0][0] + y*matrizT[1][0] + z*matrizT[2][0] + matrizT[3][0];
    double yN = x*matrizT[0][1] + y*matrizT[1][1] + z*matrizT[2][1] + matrizT[3][1];
    double zN = x*matrizT[0][2] + y*matrizT[1][2] + z*matrizT[2][2] + matrizT[3][2];
    x = xN;
    y = yN;
    z = zN;
}

void Ponto::setarX(double nx){
    x = nx;
}

void Ponto::setarY(double ny){
    y = ny;
}

void Ponto::setarZ(double nz){
    z = nz;
}

bool Ponto::operator ==(Ponto ponto){
    return (this->x == ponto.obterX() && this->y == ponto.obterY());
}

void Ponto::normalizarVetor(){
    double modulo = sqrt(x*x + y*y + z*z);
    x = x/modulo;
    y = y/modulo;
    z = z/modulo;
}
