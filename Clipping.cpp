#include "Clipping.h"

Clipping::Clipping(double xMin,double xMax,double yMin,double yMax){
    this->xMin = xMin;
    this->xMax = xMax;
    this->yMin = yMin;
    this->yMax = yMax;
}

int Clipping::identificarRC(Ponto const &p){
    int rc = 0;
    if(p.obterX() <= xMin)
        rc += E;
    if(p.obterX() >= xMax)
        rc += D;
    if(p.obterY() <= yMin)
        rc += B;
    if(p.obterY() >= yMax)
        rc += C;
    return rc;
}

bool Clipping::clippingDePonto(Ponto &ponto){
    return (ponto.obterX()>xMin && ponto.obterX()<xMax && ponto.obterY()>yMin && ponto.obterY()<yMax);
}

bool Clipping::clippingDeLinhaCohen(Ponto const &p1, Ponto const &p2, Ponto &np1, Ponto &np2){
    int rc1, rc2;
    rc1 = identificarRC(p1);
    rc2 = identificarRC(p2);
    if(rc1 == M && rc2 == M){ // Totalmente dentro
        np1 = p1;
        np2 = p2;
        return true;
    } else if ((rc1 & rc2) != 0){ // Totalmente fora
        return false;
    } else{ // Parcialmente dentro

        // TODO
        np1 = p1;
        np2 = p2;
        return true;
    }
}


