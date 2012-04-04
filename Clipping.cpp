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
        bool clipou = false;
        double m = (p2.obterY()-p1.obterY())/(p2.obterX()-p1.obterX());
        if (rc1 != 0)
            if(calculaNovoPonto(m, rc1, p1, np1))
                clipou = true;
        if (rc2 != 0)
            if(calculaNovoPonto(m, rc2, p2, np2))
                clipou = true;
        return clipou;
    }
}

bool Clipping::calculaNovoPonto(double m, int rc, Ponto const &p, Ponto &np){
    bool clipou = false;
    double nc;
    if(rc == B || rc == BE || rc == BD){
        nc = p.obterX()+(yMin - p.obterY())/m;
        if(nc>xMin && nc<xMax){
            np.setarX(nc);
            np.setarY(yMin);
            clipou = true;
        }
    }
    if(rc == C || rc == CE || rc == CD){
        nc = p.obterX()+(yMax - p.obterY())/m;
        if(nc>xMin && nc<xMax){
            np.setarX(nc);
            np.setarY(yMax);
            clipou = true;
        }
    }
    if(rc == E || rc == BE || rc == CE){
        nc = p.obterY()+(xMin - p.obterX())*m;
        if(nc>yMin && nc<yMax){
            np.setarY(nc);
            np.setarX(xMin);
            clipou = true;
        }
    }
    if(rc == D || rc == BD || rc == CD){
        nc = p.obterY()+(xMax - p.obterX())*m;
        if(nc>yMin && nc<yMax){
            np.setarY(nc);
            np.setarX(xMax);
            clipou = true;
        }
    }
    return clipou;
}


