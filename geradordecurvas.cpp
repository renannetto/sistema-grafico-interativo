#include "geradordecurvas.h"

GeradorDeCurvas::GeradorDeCurvas()
{
    nPassos = 10;
    forward = false;
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
    double constantesX[4], constantesY[4], constantesZ[4];
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
    double f0z;
    double deltaf0x;
    double deltaf0y;
    double deltaf0z;
    double delta2f0x;
    double delta2f0y;
    double delta2f0z;
    double delta3f0x;
    double delta3f0y;
    double delta3f0z;

    for(unsigned int i = 0; i < pontos.size()-3; i++){
        for(int j = 0; j < 4; j++){
            constantesX[j] = 0;
            constantesY[j] = 0;
            constantesZ[j] = 0;

            constantesX[j] += matrizBSpline[j][0]*p1->obterX();
            constantesY[j] += matrizBSpline[j][0]*p1->obterY();
            constantesZ[j] += matrizBSpline[j][0]*p1->obterZ();
            constantesX[j] += matrizBSpline[j][1]*p2->obterX();
            constantesY[j] += matrizBSpline[j][1]*p2->obterY();
            constantesZ[j] += matrizBSpline[j][1]*p2->obterZ();
            constantesX[j] += matrizBSpline[j][2]*p3->obterX();
            constantesY[j] += matrizBSpline[j][2]*p3->obterY();
            constantesZ[j] += matrizBSpline[j][2]*p3->obterZ();
            constantesX[j] += matrizBSpline[j][3]*p4->obterX();
            constantesY[j] += matrizBSpline[j][3]*p4->obterY();
            constantesZ[j] += matrizBSpline[j][3]*p4->obterZ();
        }
        if (forward) {
            f0x = constantesX[3];
            f0y = constantesY[3];
            f0z = constantesZ[3];
            deltaf0x = deltinha3*constantesX[0] + deltinha2*constantesX[1] + deltinha*constantesX[2];
            deltaf0y = deltinha3*constantesY[0] + deltinha2*constantesY[1] + deltinha*constantesY[2];
            deltaf0z = deltinha3*constantesZ[0] + deltinha2*constantesZ[1] + deltinha*constantesZ[2];
            delta2f0x = deltinha3_2*constantesX[0] + deltinha2_2*constantesX[1];
            delta2f0y = deltinha3_2*constantesY[0] + deltinha2_2*constantesY[1];
            delta2f0z = deltinha3_2*constantesZ[0] + deltinha2_2*constantesZ[1];
            delta3f0x = deltinha3_2*constantesX[0];
            delta3f0y = deltinha3_2*constantesY[0];
            delta3f0z = deltinha3_2*constantesZ[0];
            Ponto ponto(f0x, f0y, f0z);
            Ponto delta(deltaf0x, deltaf0y, deltaf0z);
            Ponto delta2(delta2f0x, delta2f0y, delta2f0z);
            Ponto delta3(delta3f0x, delta3f0y, delta3f0z);
            forwardDifferences(ponto, delta, delta2, delta3, nPontos);
        }
        else
            gerarBSplineBlending(constantesX, constantesY, constantesZ, nPontos);

        p1 = p2;
        p2 = p3;
        p3 = p4;
        p4 = (*it);
        it++;
    }
}

void GeradorDeCurvas::gerarBezier(list<Ponto*> &pontos, list<Ponto*> &nPontos) {
    list<Ponto*>::iterator it = pontos.begin();
    double constantesX[4], constantesY[4], constantesZ[4];
    for(unsigned int i = 0; i < (pontos.size()-1)/3; i++){
        Ponto* p1 = *it++;
        Ponto* p2 = *it++;
        Ponto* p3 = *it++;
        Ponto* p4 = *it;
        for(int j = 0; j < 4; j++){
	    constantesX[j] = 0;
	    constantesY[j] = 0;
	    constantesZ[j] = 0;

	    constantesX[j] += matrizBSpline[j][0]*p1->obterX();
	    constantesY[j] += matrizBSpline[j][0]*p1->obterY();
	    constantesZ[j] += matrizBSpline[j][0]*p1->obterZ();
	    constantesX[j] += matrizBSpline[j][1]*p2->obterX();
	    constantesY[j] += matrizBSpline[j][1]*p2->obterY();
	    constantesZ[j] += matrizBSpline[j][1]*p2->obterZ();
	    constantesX[j] += matrizBSpline[j][2]*p3->obterX();
	    constantesY[j] += matrizBSpline[j][2]*p3->obterY();
	    constantesZ[j] += matrizBSpline[j][2]*p3->obterZ();
	    constantesX[j] += matrizBSpline[j][3]*p4->obterX();
	    constantesY[j] += matrizBSpline[j][3]*p4->obterY();
	    constantesZ[j] += matrizBSpline[j][3]*p4->obterZ();
        }
	double x1,x2,y1,y2,z1,z2;
        x1 = constantesX[3];
        y1 = constantesY[3];
	z1 = constantesZ[3];
	nPontos.push_back(new Ponto(x1, y1, z1));
        for(int j = 1; j <= nPassos; j++){
            double passo = (double)j/(double)nPassos;
            x2 = ((constantesX[0]*passo + constantesX[1])*passo + constantesX[2])*passo + constantesX[3];
            y2 = ((constantesY[0]*passo + constantesY[1])*passo + constantesY[2])*passo + constantesY[3];
	    z2 = ((constantesZ[0]*passo + constantesZ[1])*passo + constantesZ[2])*passo + constantesZ[3];

	    nPontos.push_back(new Ponto(x2, y2, z2));

            x1 = x2;
            y1 = y2;
	    z1 = z2;
        }
    }
}

void GeradorDeCurvas::gerarBSplineBlending(double constantesX[], double constantesY[], double constantesZ[], list<Ponto *> &nPontos) {
    double x1,x2,y1,y2,z1,z2;
    x1 = constantesX[3];
    y1 = constantesY[3];
    z1 = constantesZ[3];
    nPontos.push_back(new Ponto(x1, y1, z1));
    for(int j = 1; j <= nPassos; j++){
        double passo = (double)j/(double)nPassos;
        x2 = ((constantesX[0]*passo + constantesX[1])*passo + constantesX[2])*passo + constantesX[3];
        y2 = ((constantesY[0]*passo + constantesY[1])*passo + constantesY[2])*passo + constantesY[3];
	z2 = ((constantesZ[0]*passo + constantesZ[1])*passo + constantesZ[2])*passo + constantesZ[3];

	nPontos.push_back(new Ponto(x2, y2, z2));

        x1 = x2;
        y1 = y2;
	z1 = z2;
    }
}

void GeradorDeCurvas::forwardDifferences(Ponto &ponto, Ponto &delta, Ponto &delta2, Ponto &delta3, list<Ponto *> &nPontos) {
    double x = ponto.obterX();
    double y = ponto.obterY();
    double z = ponto.obterY();
    double deltax = delta.obterX();
    double deltay = delta.obterY();
    double deltaz = delta.obterZ();
    double delta2x = delta2.obterX();
    double delta2y = delta2.obterY();
    double delta2z = delta2.obterZ();
    double delta3x = delta3.obterX();
    double delta3y = delta3.obterY();
    double delta3z = delta3.obterZ();

    nPontos.push_back(new Ponto(x, y, z));
    for (int i=0; i<nPassos; i++) {
        x += deltax;
        deltax += delta2x;
        delta2x += delta3x;
        y += deltay;
        deltay += delta2y;
        delta2y += delta3y;
	z += deltaz;
	deltaz += delta2z;
	delta2z += delta3z;
	nPontos.push_back(new Ponto(x, y, z));
    }
}

void GeradorDeCurvas::fixarForward(bool vForward) {
    forward = vForward;
}
