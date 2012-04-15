#include "geradordecurvas.h"

GeradorDeCurvas::GeradorDeCurvas()
{
    nPassos = 20;
    forward = true;
    construirMatrizes();
}

void GeradorDeCurvas::construirMatrizes(){
    matrizBezier[0][0] = -1; matrizBezier[0][1] = 3; matrizBezier[0][2] = -3; matrizBezier[0][3] = 1;
    matrizBezier[1][0] = 3; matrizBezier[1][1] = -6; matrizBezier[1][2] = 3; matrizBezier[1][3] = 0;
    matrizBezier[2][0] = -3; matrizBezier[2][1] = 3; matrizBezier[2][2] = 0; matrizBezier[2][3] = 0;
    matrizBezier[3][0] = 1; matrizBezier[3][1] = 0; matrizBezier[3][2] = 0; matrizBezier[3][3] = 0;

    matrizBSpline[0][0] = (double)-1/6; matrizBSpline[0][1] = (double)3/6; matrizBSpline[0][2] = (double)-3/6; matrizBSpline[0][3] = (double)1/6;
    matrizBSpline[1][0] = (double)3/6; matrizBSpline[1][1] = -1; matrizBSpline[1][2] = (double)3/6; matrizBSpline[1][3] = 0;
    matrizBSpline[2][0] = (double)-3/6; matrizBSpline[2][1] = 0; matrizBSpline[2][2] = (double)3/6; matrizBSpline[2][3] = 0;
    matrizBSpline[3][0] = (double)1/6; matrizBSpline[3][1] = (double)4/6; matrizBSpline[3][2] = (double)1/6; matrizBSpline[3][3] = 0;
}

void GeradorDeCurvas::gerarBSpline(list<Ponto *> &pontos, list<Ponto *> &nPontos) {
    list<Ponto*>::iterator it = pontos.begin();
    double constantesX[4], constantesY[4];
    Ponto* p1 = *it++;
    Ponto* p2 = *it++;
    Ponto* p3 = *it++;
    Ponto* p4 = *it++;
    double deltinha = (double)1/(double)nPassos;
    double deltinha2 = deltinha*deltinha;
    double deltinha2_2 = 2*deltinha2;
    double deltinha3 = deltinha2*deltinha;
    double deltinha3_2 = 6*deltinha3;

    double f0x;
    double f0y;
    double deltaf0x;
    double deltaf0y;
    double delta2f0x;
    double delta2f0y;
    double delta3f0x;
    double delta3f0y;

    for(int i = 0; i < pontos.size()-3; i++){
        for(int j = 0; j < 4; j++){
            constantesX[j] = 0;
            constantesY[j] = 0;

            constantesX[j] += matrizBSpline[j][0]*p1->obterX();
            constantesY[j] += matrizBSpline[j][0]*p1->obterY();
            constantesX[j] += matrizBSpline[j][1]*p2->obterX();
            constantesY[j] += matrizBSpline[j][1]*p2->obterY();
            constantesX[j] += matrizBSpline[j][2]*p3->obterX();
            constantesY[j] += matrizBSpline[j][2]*p3->obterY();
            constantesX[j] += matrizBSpline[j][3]*p4->obterX();
            constantesY[j] += matrizBSpline[j][3]*p4->obterY();
        }
        if (forward) {
            f0x = constantesX[3];
            f0y = constantesY[3];
            deltaf0x = deltinha3*constantesX[0] + deltinha2*constantesX[1] + deltinha*constantesX[2];
            deltaf0y = deltinha3*constantesY[0] + deltinha2*constantesY[1] + deltinha*constantesY[2];
            delta2f0x = deltinha3_2*constantesX[0] + deltinha2_2*constantesX[1];
            delta2f0y = deltinha3_2*constantesY[0] + deltinha2_2*constantesY[1];
            delta3f0x = deltinha3_2*constantesX[0];
            delta3f0y = deltinha3_2*constantesY[0];
            Ponto ponto(f0x, f0y);
            Ponto delta(deltaf0x, deltaf0y);
            Ponto delta2(delta2f0x, delta2f0y);
            Ponto delta3(delta3f0x, delta3f0y);
            forwardDifferences(ponto, delta, delta2, delta3, nPontos);
        }
        else
            gerarBSplineBlending(constantesX, constantesY, nPontos);

        p1 = p2;
        p2 = p3;
        p3 = p4;
        p4 = (*it);
        it++;
    }
}

void GeradorDeCurvas::gerarBezier(list<Ponto*> &pontos, list<Ponto*> &nPontos) {
    list<Ponto*>::iterator it = pontos.begin();
    double constantesX[4], constantesY[4];
    for(int i = 0; i < (pontos.size()-1)/3; i++){
        Ponto* p1 = *it++;
        Ponto* p2 = *it++;
        Ponto* p3 = *it++;
        Ponto* p4 = *it;
        for(int j = 0; j < 4; j++){
            constantesX[j] = 0;
            constantesY[j] = 0;

            constantesX[j] += matrizBezier[j][0]*p1->obterX();
            constantesY[j] += matrizBezier[j][0]*p1->obterY();
            constantesX[j] += matrizBezier[j][1]*p2->obterX();
            constantesY[j] += matrizBezier[j][1]*p2->obterY();
            constantesX[j] += matrizBezier[j][2]*p3->obterX();
            constantesY[j] += matrizBezier[j][2]*p3->obterY();
            constantesX[j] += matrizBezier[j][3]*p4->obterX();
            constantesY[j] += matrizBezier[j][3]*p4->obterY();
        }
        double x1,x2,y1,y2;
        x1 = constantesX[3];
        y1 = constantesY[3];
        nPontos.push_back(new Ponto(x1, y1));
        for(int j = 1; j <= nPassos; j++){
            double passo = (double)j/(double)nPassos;
            x2 = ((constantesX[0]*passo + constantesX[1])*passo + constantesX[2])*passo + constantesX[3];
            y2 = ((constantesY[0]*passo + constantesY[1])*passo + constantesY[2])*passo + constantesY[3];

            nPontos.push_back(new Ponto(x2, y2));

            x1 = x2;
            y1 = y2;
        }
    }
}

void GeradorDeCurvas::gerarBSplineBlending(double constantesX[], double constantesY[], list<Ponto *> &nPontos) {
    double x1,x2,y1,y2;
    x1 = constantesX[3];
    y1 = constantesY[3];
    nPontos.push_back(new Ponto(x1, y1));
    for(int j = 1; j <= nPassos; j++){
        double passo = (double)j/(double)nPassos;
        x2 = ((constantesX[0]*passo + constantesX[1])*passo + constantesX[2])*passo + constantesX[3];
        y2 = ((constantesY[0]*passo + constantesY[1])*passo + constantesY[2])*passo + constantesY[3];

        nPontos.push_back(new Ponto(x2, y2));

        x1 = x2;
        y1 = y2;
    }
}

void GeradorDeCurvas::forwardDifferences(Ponto &ponto, Ponto &delta, Ponto &delta2, Ponto &delta3, list<Ponto *> &nPontos) {
    double x = ponto.obterX();
    double y = ponto.obterY();
    double deltax = delta.obterX();
    double deltay = delta.obterY();
    double delta2x = delta2.obterX();
    double delta2y = delta2.obterY();
    double delta3x = delta3.obterX();
    double delta3y = delta3.obterY();

    nPontos.push_back(new Ponto(x, y));
    for (int i=0; i<nPassos; i++) {
        x += deltax;
        deltax += delta2x;
        delta2x += delta3x;
        y += deltay;
        deltay += delta2y;
        delta2y += delta3y;
        nPontos.push_back(new Ponto(x, y));
    }
}
