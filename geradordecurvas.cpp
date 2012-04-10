#include "geradordecurvas.h"

GeradorDeCurvas::GeradorDeCurvas()
{
    nPassos = 40;
    construirMatrizes();
}

void GeradorDeCurvas::construirMatrizes(){
    matrizBezier[0][0] = -1; matrizBezier[0][1] = 3; matrizBezier[0][2] = -3; matrizBezier[0][3] = 1;
    matrizBezier[1][0] = 3; matrizBezier[1][1] = -6; matrizBezier[1][2] = 3; matrizBezier[1][3] = 0;
    matrizBezier[2][0] = -3; matrizBezier[2][1] = 3; matrizBezier[2][2] = 0; matrizBezier[2][3] = 0;
    matrizBezier[3][0] = 1; matrizBezier[3][1] = 0; matrizBezier[3][2] = 0; matrizBezier[3][3] = 0;
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
