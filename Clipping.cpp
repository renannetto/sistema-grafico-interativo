#include "Clipping.h"

Clipping::Clipping(double xMin,double xMax,double yMin,double yMax){
    this->xMin = xMin;
    this->xMax = xMax;
    this->yMin = yMin;
    this->yMax = yMax;
}

bool Clipping::clippingDePonto(Ponto &ponto){
    return (ponto.obterX()>xMin && ponto.obterX()<xMax && ponto.obterY()>yMin && ponto.obterY()<yMax);
}


