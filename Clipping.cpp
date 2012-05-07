#include "Clipping.h"

Clipping::Clipping(double xMin,double xMax,double yMin,double yMax, double zWindow, double deslocamento){
    this->xMin = xMin + (xMax-xMin)*deslocamento/100;
    this->xMax = xMax - (xMax-xMin)*deslocamento/100;
    this->yMin = yMin + (yMax-yMin)*deslocamento/100;
    this->yMax = yMax - (yMax-yMin)*deslocamento/100;
    this->zWindow = zWindow;
    distanciaZ = -800;
    clippingLinha = 0;
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
//    cout << "rc ==== " << rc << endl;
    return rc;
}

bool Clipping::calculaNovoPonto(double m, int rc, Ponto const &p, Ponto &np){
    bool clipou = false;
    double nc;
    if(rc == BAIXO || rc == BAIXOESQUERDA || rc == BAIXODIREITA){
        nc = p.obterX()+(yMin - p.obterY())/m;
        np.setarX(nc);
        np.setarY(yMin);
        clipou = true;
        if(nc>=xMin && nc<=xMax){
            return clipou;
        }
    }
    if(rc == CIMA || rc == CIMAESQUERDA || rc == CIMADIREITA){
        nc = p.obterX()+(yMax - p.obterY())/m;
        np.setarX(nc);
        np.setarY(yMax);
        clipou = true;
        if(nc>=xMin && nc<=xMax){
            return clipou;
        }
    }
    if(rc == ESQUERDA || rc == BAIXOESQUERDA || rc == CIMAESQUERDA){
        nc = p.obterY()+(xMin - p.obterX())*m;
        np.setarY(nc);
        np.setarX(xMin);
        clipou = true;
        if(nc>=yMin && nc<=yMax){
            return clipou;
        }
    }
    if(rc == DIREITA || rc == BAIXODIREITA || rc == CIMADIREITA){
        nc = p.obterY()+(xMax - p.obterX())*m;
        np.setarY(nc);
        np.setarX(xMax);
        clipou = true;
        if(nc>=yMin && nc<=yMax){
            return clipou;
        }
    }
    return clipou;
}

bool Clipping::clippingDePonto(Ponto &ponto){
    return (ponto.obterX()>xMin && ponto.obterX()<xMax && ponto.obterY()>yMin && ponto.obterY()<yMax && ponto.obterZ() < 0 && ponto.obterZ() > -800);
}

bool Clipping::clippingDeLinhaCohen(Ponto const &p1, Ponto const &p2, Ponto &np1, Ponto &np2){
    int rc1, rc2;
    rc1 = identificarRC(p1);
    rc2 = identificarRC(p2);
    np1 = p1;
    np2 = p2;
//    cout << ", rc1 = " <<rc1 <<", rc2 = " <<rc2 << endl;
    if(rc1 == MEIO && rc2 == MEIO){ // Totalmente dentro
        return true;
    } else if ((rc1 & rc2) != 0){ // Totalmente fora
        return false;
    } else{ // Parcialmente dentro
//        cout << "parcialmente dentro" << endl;
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

bool Clipping::clippingDeLinhaLiang(Ponto const &p1, Ponto const &p2, Ponto &np1, Ponto &np2) {
    double p[4];
    double q[4];
    double x1 = p1.obterX();
    double y1 = p1.obterY();
    double x2 = p2.obterX();
    double y2 = p2.obterY();
    double deltaX = x2-x1;
    double deltaY = y2-y1;

    np1 = p1;
    np2 = p2;

    p[0] = -deltaX;
    p[1] = deltaX;
    p[2] = -deltaY;
    p[3] = deltaY;

    q[0] = x1-xMin;
    q[1] = xMax-x1;
    q[2] = y1-yMin;
    q[3] = yMax-y1;

    double u1 = 0;
    double u2 = 1;
    double r;

    for (int i=0; i<4; i++) {
        r = q[i]/p[i];

        if (p[i]<0) {
            if (r>u1)
                u1 = r;
        } else {
            if (r<u2)
                u2 = r;
        }
    }

    if (u1>u2)
        return false;

    if (u1>0) {
        double xNovo1 = x1+u1*deltaX;
        double yNovo1 = y1+u1*deltaY;
        np1.setarX(xNovo1);
        np1.setarY(yNovo1);
    }

    if (u2<1) {
        double xNovo2 = x1+u2*deltaX;
        double yNovo2 = y1+u2*deltaY;
        np2.setarX(xNovo2);
        np2.setarY(yNovo2);
    }

    return true;
}

bool Clipping::clippingDeLinha(Ponto const &p1, Ponto const &p2, Ponto &np1, Ponto &np2) {
  //  if(p1.obterZ() < 0 && p2.obterZ() < 0 && p1.obterZ() > -800 && p2.obterZ() > -800) { // dentro -> dentro
    Ponto cp1 = p1;
    Ponto cp2 = p2;

    if ((p1.obterZ()>zWindow && p2.obterZ()>zWindow ) || (p2.obterZ()<distanciaZ && p1.obterZ()<distanciaZ))
        return false;
    else
        if (p1.obterZ()>zWindow || p1.obterZ()<distanciaZ) {
            double z1 = p1.obterZ();
            double z2 = p2.obterZ();
            double s = z1/(z1-z2);

            double intersecaoX = p1.obterX() + s*(p2.obterX()-p1.obterX());
            double intersecaoY = p1.obterY() + s*(p2.obterY()-p1.obterY());
            double intersecaoZ = p1.obterZ() + s*(p2.obterZ()-p1.obterZ());

            cp1.setarX(intersecaoX);
            cp1.setarY(intersecaoY);
            cp1.setarZ(intersecaoZ);
        } else if(p2.obterZ()>zWindow || p2.obterZ()<distanciaZ) {
            double z1 = p1.obterZ();
            double z2 = p2.obterZ();
            double s = z1/(z1-z2);

            double intersecaoX = p1.obterX() + s*(p2.obterX()-p1.obterX());
            double intersecaoY = p1.obterY() + s*(p2.obterY()-p1.obterY());
            double intersecaoZ = p1.obterZ() + s*(p2.obterZ()-p1.obterZ());

            cp2.setarX(intersecaoX);
            cp2.setarY(intersecaoY);
            cp2.setarZ(intersecaoZ);
        }

    if (clippingLinha)
        return clippingDeLinhaCohen(cp1, cp2, np1, np2);
    else
        return clippingDeLinhaLiang(cp1, cp2, np1, np2);
  //  }
  //  return false;
}

bool Clipping::clippingDePoligonosSutherland(list<Ponto *> &pontos, list<Ponto *> &nPontos){
    list<Ponto*> pontosTela;
    list<Ponto*> pontosEsq;
    list<Ponto*> pontosDir;
    list<Ponto*> pontosCima;
    cliparPontosPoligono(TELA, pontos, pontosTela);
    cliparPontosPoligono(BESQUERDA, pontosTela, pontosEsq);
    cliparPontosPoligono(BDIREITA, pontosEsq, pontosDir);
    cliparPontosPoligono(BCIMA, pontosDir, pontosCima);
    cliparPontosPoligono(BBAIXO, pontosCima, nPontos);
    return nPontos.size() > 0;
}

void Clipping::cliparPontosPoligono(BORDA borda, list<Ponto *> &pontos, list<Ponto *> &nPontos) {
    if (pontos.size()==0)
        return;
    list<Ponto*>::iterator it = pontos.begin();
    Ponto *ponto1 = (*it);
    Ponto *ponto2;
    for (++it; it!=pontos.end(); it++) {
        ponto2 = (*it);
        cliparRetaPoligono(borda, ponto1, ponto2, nPontos);
        ponto1 = ponto2;
    }
    ponto2 = pontos.front();
    cliparRetaPoligono(borda, ponto1, ponto2, nPontos);
}

void Clipping::cliparRetaPoligono(BORDA borda, Ponto *ponto1, Ponto *ponto2, list<Ponto*> &nPontos) {
    double m;
    switch(borda) {
    case TELA:
        if(ponto1->obterZ() < zWindow && ponto2->obterZ() < zWindow && ponto1->obterZ() > distanciaZ && ponto2->obterZ() > distanciaZ) { // dentro -> dentro
            nPontos.push_back(ponto2);
        } else
            if((ponto1->obterZ() > zWindow || ponto1->obterZ() < distanciaZ) && ponto2->obterZ() < zWindow && ponto2->obterZ() > distanciaZ) { // fora -> dentro
                double z1 = ponto1->obterZ();
                double z2 = ponto2->obterZ();
                double s = z1/(z1-z2);

                double intersecaoX = ponto1->obterX() + s*(ponto2->obterX()-ponto1->obterX());
                double intersecaoY = ponto1->obterY() + s*(ponto2->obterY()-ponto1->obterY());
                double intersecaoZ = ponto1->obterZ() + s*(ponto2->obterZ()-ponto1->obterZ());

                nPontos.push_back(new Ponto(intersecaoX, intersecaoY, intersecaoZ));
                nPontos.push_back(ponto2);
            } else
                if (ponto1->obterZ() < zWindow && ponto1->obterZ() > distanciaZ && (ponto2->obterZ() > zWindow || ponto2->obterZ() < distanciaZ)) { // dentro -> fora
                    double z1 = ponto1->obterZ();
                    double z2 = ponto2->obterZ();
                    double s = z1/(z1-z2);

                    double intersecaoX = ponto1->obterX() + s*(ponto2->obterX()-ponto1->obterX());
                    double intersecaoY = ponto1->obterY() + s*(ponto2->obterY()-ponto1->obterY());
                    double intersecaoZ = ponto1->obterZ() + s*(ponto2->obterZ()-ponto1->obterZ());

                    nPontos.push_back(new Ponto(intersecaoX, intersecaoY, intersecaoZ));
                }
        break;
    case BESQUERDA:
        if(ponto1->obterX()>=xMin && ponto2->obterX()>=xMin) { // dentro -> dentro
            nPontos.push_back(ponto2);
        } else
            if(ponto1->obterX()<xMin && ponto2->obterX()>xMin) { // fora -> dentro
                m = (ponto2->obterY()-ponto1->obterY())/(ponto2->obterX()-ponto1->obterX());
                Ponto nPonto1(ponto1->obterX(), ponto1->obterY());
                calculaNovoPonto(m, ESQUERDA, *ponto1, nPonto1);
                nPontos.push_back(new Ponto(nPonto1.obterX(), nPonto1.obterY()));
                nPontos.push_back(ponto2);
            } else
                if (ponto1->obterX()>xMin && ponto2->obterX()<xMin) { // dentro -> fora
                    m = (ponto2->obterY()-ponto1->obterY())/(ponto2->obterX()-ponto1->obterX());
                    Ponto nPonto2(ponto2->obterX(), ponto2->obterY());
                    calculaNovoPonto(m, ESQUERDA, *ponto2, nPonto2);
                    nPontos.push_back(new Ponto(nPonto2.obterX(), nPonto2.obterY()));
                }
        break;
    case BDIREITA:
        if(ponto1->obterX()<=xMax && ponto2->obterX()<=xMax) { // dentro -> dentro
            nPontos.push_back(ponto2);
        } else
            if(ponto1->obterX()>xMax && ponto2->obterX()<xMax) { // fora -> dentro
                m = (ponto2->obterY()-ponto1->obterY())/(ponto2->obterX()-ponto1->obterX());
                Ponto nPonto1(ponto1->obterX(), ponto1->obterY());
                calculaNovoPonto(m, DIREITA, *ponto1, nPonto1);
                nPontos.push_back(new Ponto(nPonto1.obterX(), nPonto1.obterY()));
                nPontos.push_back(ponto2);
            } else
                if (ponto1->obterX()<xMax && ponto2->obterX()>xMax) { // dentro -> fora
                    m = (ponto2->obterY()-ponto1->obterY())/(ponto2->obterX()-ponto1->obterX());
                    Ponto nPonto2(ponto2->obterX(), ponto2->obterY());
                    calculaNovoPonto(m, DIREITA, *ponto2, nPonto2);
                    nPontos.push_back(new Ponto(nPonto2.obterX(), nPonto2.obterY()));
                }
        break;
    case BCIMA:
        if(ponto1->obterY()<=yMax && ponto2->obterY()<=yMax) { // dentro -> dentro
            nPontos.push_back(ponto2);
        } else
            if(ponto1->obterY()>yMax && ponto2->obterY()<yMax) { // fora -> dentro
                m = (ponto2->obterY()-ponto1->obterY())/(ponto2->obterX()-ponto1->obterX());
                Ponto nPonto1(ponto1->obterX(), ponto1->obterY());
                calculaNovoPonto(m, CIMA, *ponto1, nPonto1);
                nPontos.push_back(new Ponto(nPonto1.obterX(), nPonto1.obterY()));
                nPontos.push_back(ponto2);
            } else
                if (ponto1->obterY()<yMax && ponto2->obterY()>yMax) { // dentro -> fora
                    m = (ponto2->obterY()-ponto1->obterY())/(ponto2->obterX()-ponto1->obterX());
                    Ponto nPonto2(ponto2->obterX(), ponto2->obterY());
                    calculaNovoPonto(m, CIMA, *ponto2, nPonto2);
                    nPontos.push_back(new Ponto(nPonto2.obterX(), nPonto2.obterY()));
                }
        break;
    case BBAIXO:
        if(ponto1->obterY()>=yMin && ponto2->obterY()>=yMin) { // dentro -> dentro
            nPontos.push_back(ponto2);
        } else
            if(ponto1->obterY()<yMin && ponto2->obterY()>yMin) { // fora -> dentro
                m = (ponto2->obterY()-ponto1->obterY())/(ponto2->obterX()-ponto1->obterX());
                Ponto nPonto1(ponto1->obterX(), ponto1->obterY());
                calculaNovoPonto(m, BAIXO, *ponto1, nPonto1);
                nPontos.push_back(new Ponto(nPonto1.obterX(), nPonto1.obterY()));
                nPontos.push_back(ponto2);
            } else
                if (ponto1->obterY()>yMin && ponto2->obterY()<yMin) { // dentro -> fora
                    m = (ponto2->obterY()-ponto1->obterY())/(ponto2->obterX()-ponto1->obterX());
                    Ponto nPonto2(ponto2->obterX(), ponto2->obterY());
                    calculaNovoPonto(m, BAIXO, *ponto2, nPonto2);
                    nPontos.push_back(new Ponto(nPonto2.obterX(), nPonto2.obterY()));
                }
        break;
    }
}

bool Clipping::clippingDeCurvas(list<Ponto *> &pontos, list<Ponto *> &nPontos) {
    list<Ponto*>::iterator it = pontos.begin();

    double x1 = (*it)->obterX();
    double y1 = (*it)->obterY();
    double z1 = (*it)->obterZ();
    double x2;
    double y2;
    double z2;
    bool clipou = false;

    for (++it; it!=pontos.end(); it++) {
        x2 = (*it)->obterX();
        y2 = (*it)->obterY();
        z2 = (*it)->obterZ();

        if (x1 >= xMin && x1 <= xMax && y1 >= yMin && y1 <= yMax) { //ponto 1 dentro
            if(nPontos.size() == 0){
                nPontos.push_back(new Ponto(x1,y1));
            }
            if (x2 >= xMin && x2 <= xMax && y2 >= yMin && y2 <= yMax) { //ponto 2 dentro => não precisa clipar
                nPontos.push_back(new Ponto(x2, y2));
            } else {
                Ponto p1(x1, y1);
                Ponto p2(x2, y2);
                Ponto np1(0, 0);
                Ponto np2(0, 0);
                if (clippingDeLinha(p1, p2, np1, np2)) {
                    nPontos.push_back(new Ponto(np2.obterX(), np2.obterY()));
                    clipou = true;
                }
            }
        } else { //ponto 1 fora
            if (x2 >= xMin && x2 <= xMax && y2 >= yMin && y2 <= yMax) { //ponto 2 dentro => precisa clipar
                Ponto p1(x1, y1);
                Ponto p2(x2, y2);
                Ponto np1(0, 0);
                Ponto np2(0, 0);
                if (clippingDeLinha(p1, p2, np1, np2)) {
                    if(nPontos.size() != 0){
                        nPontos.push_back(0);
                    }
                    nPontos.push_back(new Ponto(np1.obterX(), np1.obterY()));
                    nPontos.push_back(new Ponto(np2.obterX(), np2.obterY()));
                    clipou = true;
                }
            }
        }

        x1 = x2;
        y1 = y2;
        z1 = z2;
    }
    return clipou;
}

void Clipping::fixarCoordenadas(double xMin, double xMax, double yMin, double yMax, double zWindow, double deslocamento) {
    this->xMin = xMin + (xMax-xMin)*deslocamento/100;
    this->xMax = xMax - (xMax-xMin)*deslocamento/100;
    this->yMin = yMin + (yMax-yMin)*deslocamento/100;
    this->yMax = yMax - (yMax-yMin)*deslocamento/100;
    this->zWindow = zWindow;
}

void Clipping::fixarAlgoritmoDeClipping(int algoritmo) {
    clippingLinha = algoritmo;
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
