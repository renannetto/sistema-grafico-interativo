#include "geradordecurvas.h"
#include <iostream>

GeradorDeCurvas::GeradorDeCurvas()
{
    nPassos = 8;
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

void GeradorDeCurvas::gerarSuperficieBezier(list<Ponto *> &pontosSup, list<Ponto *> &nPontos) {
    Ponto* pontos[16];

    list<Ponto*>::iterator it = pontosSup.begin();

    for (int i=0; i<16; i++) {
        pontos[i] = *it++;
    }

    double passoS = 0.2;
    double passoT = 0.2;

    double s, s2, s3;
    double t, t2, t3;
    double sm[4];
    double tm[4];
    double sPX[4], sPY[4], sPZ[4];
    double nX, nY, nZ;

    for (int l=0; l<(pontosSup.size()-4)/12; l++) {
        for (int i=0; i<=nPassos; i++) {
            s = (double)i/(double)nPassos;
            s2 = s*s;
            s3 = s2*s;

            sm[0] = -s3+3*s2-3*s+1;
            sm[1] = 3*s3-6*s2+3*s;
            sm[2] = -3*s3+3*s2;
            sm[3] = s3;

            for (int j=0; j<4; j++) {
                sPX[j] = sm[0]*pontos[j]->obterX() +
                         sm[1]*pontos[j+4]->obterX() +
                         sm[2]*pontos[j+8]->obterX() +
                         sm[3]*pontos[j+12]->obterX();

                sPY[j] = sm[0]*pontos[j]->obterY() +
                         sm[1]*pontos[j+4]->obterY() +
                         sm[2]*pontos[j+8]->obterY() +
                         sm[3]*pontos[j+12]->obterY();

                sPZ[j] = sm[0]*pontos[j]->obterZ() +
                         sm[1]*pontos[j+4]->obterZ() +
                         sm[2]*pontos[j+8]->obterZ() +
                         sm[3]*pontos[j+12]->obterZ();
            }

            for (int k=0; k<=nPassos; k++) {
                t = (double)k/(double)nPassos;
                t2 = t*t;
                t3 = t2*t;

                tm[0] = -t3+3*t2-3*t+1;
                tm[1] = 3*t3-6*t2+3*t;
                tm[2] = -3*t3+3*t2;
                tm[3] = t3;

                nX = sPX[0]*tm[0] + sPX[1]*tm[1] + sPX[2]*tm[2] + sPX[3]*tm[3];
                nY = sPY[0]*tm[0] + sPY[1]*tm[1] + sPY[2]*tm[2] + sPY[3]*tm[3];
                nZ = sPZ[0]*tm[0] + sPZ[1]*tm[1] + sPZ[2]*tm[2] + sPZ[3]*tm[3];

                nPontos.push_back(new Ponto(nX, nY, nZ));

                t += passoT;
            }

            s += passoS;
        }

        for (int i=0; i<=nPassos; i++) {
            t = (double)i/(double)nPassos;
            t2 = t*t;
            t3 = t2*t;

            tm[0] = -t3+3*t2-3*t+1;
            tm[1] = 3*t3-6*t2+3*t;
            tm[2] = -3*t3+3*t2;
            tm[3] = t3;

            for (int k=0; k<=nPassos; k++) {
                s = (double)k/(double)nPassos;
                s2 = s*s;
                s3 = s2*s;

                sm[0] = -s3+3*s2-3*s+1;
                sm[1] = 3*s3-6*s2+3*s;
                sm[2] = -3*s3+3*s2;
                sm[3] = s3;

                for (int j=0; j<4; j++) {
                    sPX[j] = sm[0]*pontos[j]->obterX() +
                             sm[1]*pontos[j+4]->obterX() +
                             sm[2]*pontos[j+8]->obterX() +
                             sm[3]*pontos[j+12]->obterX();

                    sPY[j] = sm[0]*pontos[j]->obterY() +
                             sm[1]*pontos[j+4]->obterY() +
                             sm[2]*pontos[j+8]->obterY() +
                             sm[3]*pontos[j+12]->obterY();

                    sPZ[j] = sm[0]*pontos[j]->obterZ() +
                             sm[1]*pontos[j+4]->obterZ() +
                             sm[2]*pontos[j+8]->obterZ() +
                             sm[3]*pontos[j+12]->obterZ();
                }

                nX = sPX[0]*tm[0] + sPX[1]*tm[1] + sPX[2]*tm[2] + sPX[3]*tm[3];
                nY = sPY[0]*tm[0] + sPY[1]*tm[1] + sPY[2]*tm[2] + sPY[3]*tm[3];
                nZ = sPZ[0]*tm[0] + sPZ[1]*tm[1] + sPZ[2]*tm[2] + sPZ[3]*tm[3];

                nPontos.push_back(new Ponto(nX, nY, nZ));

                s += passoT;
            }

            t += passoS;
        }

        pontos[0] = pontos[3];
        pontos[4] = pontos[7];
        pontos[8] = pontos[11];
        pontos[12] = pontos[15];

        pontos[1] = *it++;
        pontos[2] = *it++;
        pontos[3] = *it++;

        pontos[5] = *it++;
        pontos[6] = *it++;
        pontos[7] = *it++;

        pontos[9] = *it++;
        pontos[10] = *it++;
        pontos[11] = *it++;

        pontos[13] = *it++;
        pontos[14] = *it++;
        pontos[15] = *it++;
    }

}

void GeradorDeCurvas::gerarSuperficieBSpline(list<Ponto *> &pontosSup, list<Ponto *> &nPontos, int nLinhas, int nColunas) {
    Ponto* pontos[16];

    list<Ponto*>::iterator it = pontosSup.begin();

    for (int i=0; i<16; i++) {
        pontos[i] = *it++;
    }

    double passoS = 0.2;
    double passoT = 0.2;

    double s, s2, s3;
    double t, t2, t3;
    double sm[4];
    double tm[4];
    double sPX[4], sPY[4], sPZ[4];
    double nX, nY, nZ;

    for (int m=0; m<nLinhas-3; m++) {
        for (int l=0; l<nColunas-3; l++) {
            for (int i=0; i<=nPassos; i++) {
                s = (double)i/(double)nPassos;
                s2 = s*s;
                s3 = s2*s;

                sm[0] = (-s3+3*s2-3*s+1)/6;
                sm[1] = (3*s3-6*s2+4)/6;
                sm[2] = (-3*s3+3*s2+3*s+1)/6;
                sm[3] = s3/6;

                for (int j=0; j<4; j++) {
                    sPX[j] = sm[0]*pontos[j]->obterX() +
                            sm[1]*pontos[j+4]->obterX() +
                            sm[2]*pontos[j+8]->obterX() +
                            sm[3]*pontos[j+12]->obterX();

                    sPY[j] = sm[0]*pontos[j]->obterY() +
                            sm[1]*pontos[j+4]->obterY() +
                            sm[2]*pontos[j+8]->obterY() +
                            sm[3]*pontos[j+12]->obterY();

                    sPZ[j] = sm[0]*pontos[j]->obterZ() +
                            sm[1]*pontos[j+4]->obterZ() +
                            sm[2]*pontos[j+8]->obterZ() +
                            sm[3]*pontos[j+12]->obterZ();
                }

                /*int indice[4];
                indice[0] = (l==0)?3:15+(l-1)*4+1;
                indice[1] = (l==0)?3+4:15+(l-1)*4+2;
                indice[2] = (l==0)?3+8:15+(l-1)*4+3;
                indice[3] = (l==0)?3+12:15+(l-1)*4+4;

                sPX[3] = sm[0]*pontos[indice[0]]->obterX() +
                        sm[1]*pontos[indice[1]]->obterX() +
                        sm[2]*pontos[indice[2]]->obterX() +
                        sm[3]*pontos[indice[3]]->obterX();

                sPY[3] = sm[0]*pontos[indice[0]]->obterY() +
                        sm[1]*pontos[indice[1]]->obterY() +
                        sm[2]*pontos[indice[2]]->obterY() +
                        sm[3]*pontos[indice[3]]->obterY();

                sPZ[3] = sm[0]*pontos[indice[0]]->obterZ() +
                        sm[1]*pontos[indice[1]]->obterZ() +
                        sm[2]*pontos[indice[2]]->obterZ() +
                        sm[3]*pontos[indice[3]]->obterZ();*/

                for (int k=0; k<=nPassos; k++) {
                    t = (double)k/(double)nPassos;
                    t2 = t*t;
                    t3 = t2*t;

                    tm[0] = (-t3+3*t2-3*t+1)/6;
                    tm[1] = (3*t3-6*t2+4)/6;
                    tm[2] = (-3*t3+3*t2+3*t+1)/6;
                    tm[3] = t3/6;

                    nX = sPX[0]*tm[0] + sPX[1]*tm[1] + sPX[2]*tm[2] + sPX[3]*tm[3];
                    nY = sPY[0]*tm[0] + sPY[1]*tm[1] + sPY[2]*tm[2] + sPY[3]*tm[3];
                    nZ = sPZ[0]*tm[0] + sPZ[1]*tm[1] + sPZ[2]*tm[2] + sPZ[3]*tm[3];

                    nPontos.push_back(new Ponto(nX, nY, nZ));

                    t += passoT;
                }

                s += passoS;
            }

            for (int i=0; i<=nPassos; i++) {
                t = (double)i/(double)nPassos;
                t2 = t*t;
                t3 = t2*t;

                tm[0] = (-t3+3*t2-3*t+1)/6;
                tm[1] = (3*t3-6*t2+4)/6;
                tm[2] = (-3*t3+3*t2+3*t+1)/6;
                tm[3] = t3/6;

                for (int k=0; k<=nPassos; k++) {
                    s = (double)k/(double)nPassos;
                    s2 = s*s;
                    s3 = s2*s;

                    sm[0] = (-s3+3*s2-3*s+1)/6;
                    sm[1] = (3*s3-6*s2+4)/6;
                    sm[2] = (-3*s3+3*s2+3*s+1)/6;
                    sm[3] = s3/6;

                    for (int j=0; j<4; j++) {
                        sPX[j] = sm[0]*pontos[j]->obterX() +
                                sm[1]*pontos[j+4]->obterX() +
                                sm[2]*pontos[j+8]->obterX() +
                                sm[3]*pontos[j+12]->obterX();

                        sPY[j] = sm[0]*pontos[j]->obterY() +
                                sm[1]*pontos[j+4]->obterY() +
                                sm[2]*pontos[j+8]->obterY() +
                                sm[3]*pontos[j+12]->obterY();

                        sPZ[j] = sm[0]*pontos[j]->obterZ() +
                                sm[1]*pontos[j+4]->obterZ() +
                                sm[2]*pontos[j+8]->obterZ() +
                                sm[3]*pontos[j+12]->obterZ();
                    }

                    /*int indice[4];
                    indice[0] = (l==0)?3:15+(l-1)*4+1;
                    indice[1] = (l==0)?3+4:15+(l-1)*4+2;
                    indice[2] = (l==0)?3+8:15+(l-1)*4+3;
                    indice[3] = (l==0)?3+12:15+(l-1)*4+4;

                    sPX[3] = sm[0]*pontos[indice[0]]->obterX() +
                            sm[1]*pontos[indice[1]]->obterX() +
                            sm[2]*pontos[indice[2]]->obterX() +
                            sm[3]*pontos[indice[3]]->obterX();

                    sPY[3] = sm[0]*pontos[indice[0]]->obterY() +
                            sm[1]*pontos[indice[1]]->obterY() +
                            sm[2]*pontos[indice[2]]->obterY() +
                            sm[3]*pontos[indice[3]]->obterY();

                    sPZ[3] = sm[0]*pontos[indice[0]]->obterZ() +
                            sm[1]*pontos[indice[1]]->obterZ() +
                            sm[2]*pontos[indice[2]]->obterZ() +
                            sm[3]*pontos[indice[3]]->obterZ();*/

                    nX = sPX[0]*tm[0] + sPX[1]*tm[1] + sPX[2]*tm[2] + sPX[3]*tm[3];
                    nY = sPY[0]*tm[0] + sPY[1]*tm[1] + sPY[2]*tm[2] + sPY[3]*tm[3];
                    nZ = sPZ[0]*tm[0] + sPZ[1]*tm[1] + sPZ[2]*tm[2] + sPZ[3]*tm[3];

                    nPontos.push_back(new Ponto(nX, nY, nZ));

                    s += passoT;
                }

                t += passoS;
            }

            pontos[0] = pontos[1];
            pontos[4] = pontos[5];
            pontos[8] = pontos[9];
            pontos[12] = pontos[13];

            pontos[1] = pontos[2];
            pontos[5] = pontos[6];
            pontos[9] = pontos[10];
            pontos[13] = pontos[14];

            pontos[2] = pontos[3];
            pontos[6] = pontos[7];
            pontos[10] = pontos[11];
            pontos[14] = pontos[15];

            pontos[3] = *it++;
            pontos[7] = *it++;
            pontos[11] = *it++;
            pontos[15] = *it++;
        }
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

int GeradorDeCurvas::obterNPassos() {
    return nPassos;
}
