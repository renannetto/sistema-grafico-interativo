#include "Clipping.h"

Clipping::Clipping(double xMin,double xMax,double yMin,double yMax, double deslocamento){
    this->xMin = xMin + (xMax-xMin)*deslocamento/100;
    this->xMax = xMax - (xMax-xMin)*deslocamento/100;
    this->yMin = yMin + (yMax-yMin)*deslocamento/100;
    this->yMax = yMax - (yMax-yMin)*deslocamento/100;
}

int Clipping::identificarRC(Ponto const &p){
    int rc = 0;
    if(p.obterX() <= xMin)
        rc += ESQUERDA;
    if(p.obterX() >= xMax)
        rc += DIREITA;
    if(p.obterY() <= yMin)
        rc += BAIXO;
    if(p.obterY() >= yMax)
        rc += CIMA;
    cout << "rc ==== " << rc << endl;
    return rc;
}

bool Clipping::calculaNovoPonto(double m, int rc, Ponto const &p, Ponto &np){
    bool clipou = false;
    double nc;
    if(rc == BAIXO || rc == BAIXOESQUERDA || rc == BAIXODIREITA){
        nc = p.obterX()+(yMin - p.obterY())/m;
        if(nc>=xMin && nc<=xMax){
            np.setarX(nc);
            np.setarY(yMin);
            clipou = true;
        }
    }
    if(rc == CIMA || rc == CIMAESQUERDA || rc == CIMADIREITA){
        nc = p.obterX()+(yMax - p.obterY())/m;
        if(nc>=xMin && nc<=xMax){
            np.setarX(nc);
            np.setarY(yMax);
            clipou = true;
        }
    }
    if(rc == ESQUERDA || rc == BAIXOESQUERDA || rc == CIMAESQUERDA){
        nc = p.obterY()+(xMin - p.obterX())*m;
        if(nc>=yMin && nc<=yMax){
            np.setarY(nc);
            np.setarX(xMin);
            clipou = true;
        }
    }
    if(rc == DIREITA || rc == BAIXODIREITA || rc == CIMADIREITA){
        nc = p.obterY()+(xMax - p.obterX())*m;
        if(nc>=yMin && nc<=yMax){
            np.setarY(nc);
            np.setarX(xMax);
            clipou = true;
        }
    }
    return clipou;
}

bool Clipping::clippingDePonto(Ponto &ponto){
    return (ponto.obterX()>xMin && ponto.obterX()<xMax && ponto.obterY()>yMin && ponto.obterY()<yMax);
}

bool Clipping::clippingDeLinhaCohen(Ponto const &p1, Ponto const &p2, Ponto &np1, Ponto &np2){
    int rc1, rc2;
    rc1 = identificarRC(p1);
    rc2 = identificarRC(p2);
    np1 = p1;
    np2 = p2;
    cout << ", rc1 = " <<rc1 <<", rc2 = " <<rc2 << endl;
    if(rc1 == MEIO && rc2 == MEIO){ // Totalmente dentro
        return true;
    } else if ((rc1 & rc2) != 0){ // Totalmente fora
        return false;
    } else{ // Parcialmente dentro
        cout << "parcialmente dentro" << endl;
        bool clipou = false;
        double m = (p2.obterY()-p1.obterY())/(p2.obterX()-p1.obterX());
        if (rc1 != MEIO)
            if(calculaNovoPonto(m, rc1, p1, np1))
                clipou = true;
        if (rc2 != MEIO)
            if(calculaNovoPonto(m, rc2, p2, np2))
                clipou = true;
        return clipou;
    }
}

bool Clipping::clippingDePoligonosWeiler(list<Ponto*> &pontos, list<Ponto*> &npontos){
    list<Ponto*>::iterator it = pontos.begin();
    bool pegouPrimeiroPonto = false;
    Ponto *ponto1 = (*it);
    Ponto *ponto2;
    Ponto *pontoInOut = new Ponto(0,0);
    Ponto *pontoOutIn = new Ponto(0,0);
    for(++it; it != pontos.end(); it++){
        ponto2 = (*it);
        if (clippingDeLinhaCohenParaWeiler(*ponto1, *ponto2, *pontoOutIn, *pontoInOut)){ //clipou, ou está completamente dentro
            if (!pegouPrimeiroPonto || !(pontoOutIn==ponto1)){
                npontos.push_back(new Ponto(pontoOutIn->obterX(), pontoOutIn->obterY()));
                pegouPrimeiroPonto = true;
            }
            cout << "pushing back ->  Ponto 1 x = " << pontoInOut->obterX() <<", Ponto 1 y = " << pontoInOut->obterY() << endl;
            npontos.push_back(new Ponto(pontoInOut->obterX(), pontoInOut->obterY()));
        }
        ponto1 = ponto2;
    }
    ponto2 = pontos.front();
    if (clippingDeLinhaCohenParaWeiler(*ponto1, *ponto2, *pontoOutIn, *pontoInOut)){
        if (!(pontoOutIn==ponto1)){
            npontos.push_back(new Ponto(pontoOutIn->obterX(), pontoOutIn->obterY()));
        }
        npontos.push_back(new Ponto(pontoInOut->obterX(), pontoInOut->obterY()));
    }

    return pegouPrimeiroPonto;
}

bool Clipping::clippingDeLinhaCohenParaWeiler(Ponto const &p1, Ponto const &p2, Ponto &pontoOutIn, Ponto &pontoInOut){
    cout << "Ponto 1 x = " << p1.obterX() <<", Ponto 1 y = " << p1.obterY() << ", Ponto 2 x = " << p2.obterX() << ", Ponto 2 y = " << p2.obterY() << endl;
    int rc1, rc2;
    rc1 = identificarRC(p1);
    rc2 = identificarRC(p2);
    pontoOutIn = p1;
    pontoInOut = p2;
    if(rc1 == MEIO && rc2 == MEIO){ // Totalmente dentro
        cout << "Totalmente Dentro" << endl;
        return true;
    } else if ((rc1 & rc2) != 0){ // Totalmente fora
//        cout << "Ponto 1 x = " << p1.obterX() <<", Ponto 1 y = " << p1.obterY() <<
//                ", Ponto 2 x = " << p2.obterX() << ", Ponto 2 y = " << p2.obterY() << ", rc1 = " <<rc1 <<", rc2 = " <<rc2 << endl;
//        cout << "Totalmente Fora" << endl;

        return false;
    } else{ // Parcialmente dentro
        cout << "Parcialmente Dentro" << endl;

        bool clipou = false;
        double m = (p2.obterY()-p1.obterY())/(p2.obterX()-p1.obterX());
        if (rc1 != MEIO)
            if(calculaNovoPonto(m, rc1, p1, pontoOutIn))
                clipou = true;
        if (rc2 != MEIO)
            if(calculaNovoPonto(m, rc2, p2, pontoInOut))
                clipou = true;
        return clipou;
    }
}

void Clipping::fixarCoordenadas(double xMin, double xMax, double yMin, double yMax, double deslocamento) {
    this->xMin = xMin + (xMax-xMin)*deslocamento/100;
    this->xMax = xMax - (xMax-xMin)*deslocamento/100;
    this->yMin = yMin + (yMax-yMin)*deslocamento/100;
    this->yMax = yMax - (yMax-yMin)*deslocamento/100;
}

double Clipping::obterXMax(){
    return xMax;
}

double Clipping::obterXMin(){
    return xMin;
}

double Clipping::obterYMax(){
    return yMax;
}

double Clipping::obterYMin(){
    return yMin;
}
