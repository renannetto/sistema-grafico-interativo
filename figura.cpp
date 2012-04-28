#include "figura.h"

Figura::Figura(string vNome, Tipo vTipo, list<Ponto *> vPontos, list<Face*> vFaces, Cor vCor, Ponto vrp, double tetaX, double tetaY, Ponto centroDaCamera, double teta)
    : cor(vCor)
{
    nome = vNome;
    tipo = vTipo;
    pontos = vPontos;
    faces = vFaces;

    pontosPPC = pontos;

    matrizT = new double*[4];
    for(int i = 0; i < 4; i++)
        matrizT[i] = new double[4];

    alinharComZ(tetaX, tetaY, centroDaCamera);
    gerarDescricaoPPC(teta);
}

Figura::~Figura()
{
}

list<Ponto*> Figura::obterPontos(){
    return pontos;
}

list<Face*> Figura::obterFaces() {
    return faces;
}

list<Ponto*> Figura::obterPontosPPC(){
    return pontosPPC;
}

string Figura::obterNome(){
    return nome;
}

Tipo Figura::obterTipo(){
    return tipo;
}

Cor Figura::obterCor(){
    return cor;
}

void Figura::transladar(double vX, double vY, double vZ) {
    matrizT[0][0] = 1; matrizT[0][1] = 0; matrizT[0][2] = 0; matrizT[0][3] = 0;
    matrizT[1][0] = 0; matrizT[1][1] = 1; matrizT[1][2] = 0; matrizT[0][3] = 0;
    matrizT[2][0] = 0; matrizT[2][1] = 0; matrizT[2][2] = 1; matrizT[2][3] = 0;
    matrizT[3][0] = vX; matrizT[3][1] = vY; matrizT[3][2] = vZ; matrizT[3][3] = 1;
    transformar();
}

void Figura::escalonar(double vX, double vY, double vZ){
    Ponto centro = obterCentro();
    double xMedio = centro.obterX();
    double yMedio = centro.obterY();
    double zMedio = centro.obterZ();

    matrizT[0][0] = vX; matrizT[0][1] = 0; matrizT[0][2] = 0; matrizT[0][3] = 0;
    matrizT[1][0] = 0; matrizT[1][1] = vY; matrizT[1][2] = 0; matrizT[1][3] = 0;
    matrizT[2][0] = 0; matrizT[2][1] = 0; matrizT[2][2] = vZ; matrizT[2][3] = 0;
    matrizT[3][0] = xMedio*(1-vX); matrizT[3][1] = yMedio*(1-vY); matrizT[3][2] = zMedio*(1-vZ); matrizT[3][3] = 1;
    transformar();
}

void Figura::rotacionarNaOrigem(double teta, Ponto vetor) {
    double ux = vetor.obterX();
    double uy = vetor.obterY();
    double uz = vetor.obterZ();

    teta = teta*M_PI/180;

    double cosTeta = cos(teta);
    double sinTeta = sin(teta);

    /*double cosTetax = cos(0);         Matriz multiplicada a mão -- não funcionando
    double sinTetax = sin(0);
    double cosTetaz = cos(M_PI/2);
    double sinTetaz = cos(M_PI/2);

    matrizT[0][0] = cosTeta*cosTetaz*cosTetaz+sinTetaz*sinTetaz;
    matrizT[0][1] = cosTetaz*(cosTeta*(-sinTetaz)*cosTetax - sinTeta*sinTetax) + sinTetaz*cosTetaz*cosTetax;
    matrizT[0][2] = cosTetaz*(cosTeta*sinTetaz*sinTetax - sinTeta*cosTetax) + sinTetaz*cosTetaz*(-sinTetax);
    matrizT[0][3] = 0;

    matrizT[1][0] = cosTetax*(-sinTetaz*cosTeta*cosTetaz + cosTetaz*sinTetaz) + sinTetax*(sinTeta*cosTetaz);
    matrizT[1][1] = cosTetax*(-sinTetaz*(cosTeta*(-sinTetaz)*cosTetax - sinTeta*sinTetax) + cosTetaz*cosTetaz*cosTetax) + sinTetax*(sinTeta*(-sinTetaz)*cosTetax + cosTeta*sinTetax);
    matrizT[1][2] = cosTetax*(-sinTetaz*(cosTeta*sinTetaz*sinTetax - sinTeta*cosTetax) + cosTetaz*cosTetaz*(-sinTetax)) + sinTetax*(sinTeta*sinTetaz*sinTetax + cosTeta*cosTetax);
    matrizT[1][3] = 0;

    matrizT[2][0] = -sinTetax*(-sinTetaz*cosTeta*cosTetaz + cosTetaz*sinTetaz) + cosTetax*(sinTeta*cosTetaz);
    matrizT[2][1] = -sinTetax*(-sinTetaz*(cosTeta*(-sinTetaz)*cosTetax - sinTeta*sinTetax) + cosTetaz*cosTetaz*cosTetax) + cosTetax*(sinTeta*(-sinTetaz)*cosTetax + cosTeta*sinTetax);
    matrizT[2][2] = -sinTetax*(-sinTetaz*(cosTeta*sinTetaz*sinTetax - sinTeta*cosTetax) + cosTetaz*cosTetaz*(-sinTetax)) + cosTetax*(sinTeta*sinTetaz*sinTetax + cosTeta*cosTetax);
    matrizT[2][3] = 0;

    matrizT[3][0] = 0;
    matrizT[3][1] = 0;
    matrizT[3][2] = 0;
    matrizT[3][3] = 1;*/

    matrizT[0][0] = cosTeta + ux*ux*(1-cosTeta); matrizT[0][1] = ux*uy*(1-cosTeta) - uz*sinTeta; matrizT[0][2] = ux*uz*(1-cosTeta) + uy*sinTeta; matrizT[0][3] = 0;
    matrizT[1][0] = uy*ux*(1-cosTeta) + uz*sinTeta; matrizT[1][1] = cosTeta + uy*uy*(1-cosTeta); matrizT[1][2] = uy*uz*(1-cosTeta) - ux*sinTeta; matrizT[1][3] = 0;
    matrizT[2][0] = uz*ux*(1-cosTeta) - uy*sinTeta; matrizT[2][1] = uz*uy*(1-cosTeta) + ux*sinTeta; matrizT[2][2] = cosTeta + uz*uz*(1-cosTeta); matrizT[2][3] = 0;
    matrizT[3][0] = 0; matrizT[3][1] = 0; matrizT[3][2] = 0; matrizT[3][3] = 1;

    transformar();
}

void Figura::rotacionarNoCentro(double teta, Ponto vetor){
    double ux = vetor.obterX();
    double uy = vetor.obterY();
    double uz = vetor.obterZ();

    Ponto centro = obterCentro();
    double pX = centro.obterX();
    double pY = centro.obterY();
    double pZ = centro.obterZ();

    teta = teta*M_PI/180;

    double cosTeta = cos(teta);
    double sinTeta = sin(teta);

    matrizT[0][0] = cosTeta + ux*ux*(1-cosTeta); matrizT[0][1] = ux*uy*(1-cosTeta) - uz*sinTeta; matrizT[0][2] = ux*uz*(1-cosTeta) + uy*sinTeta; matrizT[0][3] = 0;
    matrizT[1][0] = uy*ux*(1-cosTeta) + uz*sinTeta; matrizT[1][1] = cosTeta + uy*uy*(1-cosTeta); matrizT[1][2] = uy*uz*(1-cosTeta) - ux*sinTeta; matrizT[1][3] = 0;
    matrizT[2][0] = uz*ux*(1-cosTeta) - uy*sinTeta; matrizT[2][1] = uz*uy*(1-cosTeta) + ux*sinTeta; matrizT[2][2] = cosTeta + uz*uz*(1-cosTeta); matrizT[2][3] = 0;
    matrizT[3][0] = pX*(1-matrizT[0][0]) - pY*matrizT[1][0] - pZ*matrizT[2][0]; matrizT[3][1] = -pX*matrizT[0][1] + pY*(1-matrizT[1][1]) - pZ*matrizT[2][1];
    matrizT[3][2] = -pX*matrizT[0][2] - pY*matrizT[1][2] + pZ*(1-matrizT[2][2]); matrizT[3][3] = 1;

    transformar();
}

void Figura::rotacionarNoPonto(double teta, double pX, double pY, double pZ, Ponto vetor){
    double ux = vetor.obterX();
    double uy = vetor.obterY();
    double uz = vetor.obterZ();

    teta = teta*M_PI/180;

    double cosTeta = cos(teta);
    double sinTeta = sin(teta);

    matrizT[0][0] = cosTeta + ux*ux*(1-cosTeta); matrizT[0][1] = ux*uy*(1-cosTeta) - uz*sinTeta; matrizT[0][2] = ux*uz*(1-cosTeta) + uy*sinTeta; matrizT[0][3] = 0;
    matrizT[1][0] = uy*ux*(1-cosTeta) + uz*sinTeta; matrizT[1][1] = cosTeta + uy*uy*(1-cosTeta); matrizT[1][2] = uy*uz*(1-cosTeta) - ux*sinTeta; matrizT[1][3] = 0;
    matrizT[2][0] = uz*ux*(1-cosTeta) - uy*sinTeta; matrizT[2][1] = uz*uy*(1-cosTeta) + ux*sinTeta; matrizT[2][2] = cosTeta + uz*uz*(1-cosTeta); matrizT[2][3] = 0;
    matrizT[3][0] = pX*(1-matrizT[0][0]) - pY*matrizT[1][0] - pZ*matrizT[2][0]; matrizT[3][1] = -pX*matrizT[0][1] + pY*(1-matrizT[1][1]) - pZ*matrizT[2][1];
    matrizT[3][2] = -pX*matrizT[0][2] - pY*matrizT[1][2] + pZ*(1-matrizT[2][2]); matrizT[3][3] = 1;

    transformar();
}

void Figura::transformar(){
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        (*it)->transformar(matrizT);
    }
}

void Figura::mudarCor(int vermelho, int verde, int azul){
    cor = Cor(vermelho, verde, azul);
}

void Figura::alinharComZ(double tetaX, double tetaY, Ponto centroDaCamera) {
    double wcX = centroDaCamera.obterX();
    double wcY = centroDaCamera.obterY();
    double wcZ = centroDaCamera.obterZ();

    double cosTeta;
    double sinTeta;

    list<Ponto*>::iterator it;

    for (it = pontos.begin(); it != pontos.end(); it++){
        pontosPPC.pop_front();
        pontosPPC.push_back(new Ponto((*it)->obterX(), (*it)->obterY(), (*it)->obterZ()));
    }

    //Transladar o vrp para a origem
    matrizT[0][0] = 1; matrizT[0][1] = 0; matrizT[0][2] = 0; matrizT[0][3] = 0;
    matrizT[1][0] = 0; matrizT[1][1] = 1; matrizT[1][2] = 0; matrizT[0][3] = 0;
    matrizT[2][0] = 0; matrizT[2][1] = 0; matrizT[2][2] = 1; matrizT[2][3] = 0;
    matrizT[3][0] = -wcX; matrizT[3][1] = -wcY; matrizT[3][2] = -wcZ; matrizT[3][3] = 1;

    for(it = pontosPPC.begin(); it != pontosPPC.end(); it++){
        (*it)->transformar(matrizT);
    }

    tetaY = -(tetaY + M_PI/2);

    cosTeta = cos(tetaY);
    sinTeta = sin(tetaY);

    //Rotacionar ao redor do eixo y
    matrizT[0][0] = cosTeta; matrizT[0][1] = 0; matrizT[0][2] = -sinTeta; matrizT[0][3] = 0;
    matrizT[1][0] = 0; matrizT[1][1] = 1; matrizT[1][2] = 0; matrizT[0][3] = 0;
    matrizT[2][0] = sinTeta; matrizT[2][1] = 0; matrizT[2][2] = cosTeta; matrizT[2][3] = 0;
    matrizT[3][0] = 0; matrizT[3][1] = 0; matrizT[3][2] = 0; matrizT[3][3] = 1;

    for(it = pontosPPC.begin(); it != pontosPPC.end(); it++){
        (*it)->transformar(matrizT);
    }

    tetaX = -(M_PI/2 - tetaX);

    cosTeta = cos(tetaX);
    sinTeta = sin(tetaX);

    //Rotacionar ao redor do eixo x
    matrizT[0][0] = 1; matrizT[0][1] = 0; matrizT[0][2] = 0; matrizT[0][3] = 0;
    matrizT[1][0] = 0; matrizT[1][1] = cosTeta; matrizT[1][2] = sinTeta; matrizT[0][3] = 0;
    matrizT[2][0] = 0; matrizT[2][1] = -sinTeta; matrizT[2][2] = cosTeta; matrizT[2][3] = 0;
    matrizT[3][0] = 0; matrizT[3][1] = 0; matrizT[3][2] = 0; matrizT[3][3] = 1;

    for(it = pontosPPC.begin(); it != pontosPPC.end(); it++){
        (*it)->transformar(matrizT);
    }

    //Desconsidera o z
//    for(it = pontosPPC.begin(); it != pontosPPC.end(); it++){
//        (*it)->setarZ(0);
//    }
}

void Figura::gerarDescricaoPPC(double teta){

    teta = -teta*M_PI/180;

    double cosTeta = cos(teta);
    double sinTeta = sin(teta);

    matrizT[0][0] = cosTeta; matrizT[0][1] = sinTeta; matrizT[0][2] = 0; matrizT[0][3] = 0;
    matrizT[1][0] = -sinTeta; matrizT[1][1] = cosTeta; matrizT[1][2] = 0; matrizT[0][3] = 0;
    matrizT[2][0] = 0; matrizT[2][1] = 0; matrizT[2][2] = 1; matrizT[2][3] = 0;
    matrizT[3][0] = 0; matrizT[3][1] = 0; matrizT[3][2] = 0; matrizT[3][3] = 1;

    list<Ponto*>::iterator it;
    for(it = pontosPPC.begin(); it != pontosPPC.end(); it++){
        (*it)->transformar(matrizT);
    }

//    ux = 1;
//    uy = 0;
//    uz = 0;

//    Ponto centro = obterCentro();
//    pX = centro.obterX();
//    pY = centro.obterY();
//    pZ = centro.obterZ();


//    matrizT[0][0] = cosTeta + ux*ux*(1-cosTeta); matrizT[0][1] = ux*uy*(1-cosTeta) - uz*sinTeta; matrizT[0][2] = ux*uz*(1-cosTeta) + uy*sinTeta; matrizT[0][3] = 0;
//    matrizT[1][0] = uy*ux*(1-cosTeta) + uz*sinTeta; matrizT[1][1] = cosTeta + uy*uy*(1-cosTeta); matrizT[1][2] = uy*uz*(1-cosTeta) - ux*sinTeta; matrizT[1][3] = 0;
//    matrizT[2][0] = uz*ux*(1-cosTeta) - uy*sinTeta; matrizT[2][1] = uz*uy*(1-cosTeta) + ux*sinTeta; matrizT[2][2] = cosTeta + uz*uz*(1-cosTeta); matrizT[2][3] = 0;
//    matrizT[3][0] = pX*(1-matrizT[0][0]) - pY*matrizT[1][0] - pZ*matrizT[2][0]; matrizT[3][1] = -pX*matrizT[0][1] + pY*(1-matrizT[1][1]) - pZ*matrizT[2][1];
//    matrizT[3][2] = -pX*matrizT[0][2] - pY*matrizT[1][2] + pZ*(1-matrizT[2][2]); matrizT[3][3] = 1;

//    ux = 0;
//    uy = 1;
//    uz = 0;

//    centro = obterCentro();
//    pX = centro.obterX();
//    pY = centro.obterY();
//    pZ = centro.obterZ();


//    matrizT[0][0] = cosTeta + ux*ux*(1-cosTeta); matrizT[0][1] = ux*uy*(1-cosTeta) - uz*sinTeta; matrizT[0][2] = ux*uz*(1-cosTeta) + uy*sinTeta; matrizT[0][3] = 0;
//    matrizT[1][0] = uy*ux*(1-cosTeta) + uz*sinTeta; matrizT[1][1] = cosTeta + uy*uy*(1-cosTeta); matrizT[1][2] = uy*uz*(1-cosTeta) - ux*sinTeta; matrizT[1][3] = 0;
//    matrizT[2][0] = uz*ux*(1-cosTeta) - uy*sinTeta; matrizT[2][1] = uz*uy*(1-cosTeta) + ux*sinTeta; matrizT[2][2] = cosTeta + uz*uz*(1-cosTeta); matrizT[2][3] = 0;
//    matrizT[3][0] = pX*(1-matrizT[0][0]) - pY*matrizT[1][0] - pZ*matrizT[2][0]; matrizT[3][1] = -pX*matrizT[0][1] + pY*(1-matrizT[1][1]) - pZ*matrizT[2][1];
//    matrizT[3][2] = -pX*matrizT[0][2] - pY*matrizT[1][2] + pZ*(1-matrizT[2][2]); matrizT[3][3] = 1;


//    ux = 0;
//    uy = 0;
//    uz = 1;

//    pX = wcX;
//    pY = wcY;
//    pZ = wcZ;

    //Translada (-wcX, -wcY, -wcZ) para o PPC
//    matrizT[0][0] = 1; matrizT[0][1] = 0; matrizT[0][2] = 0; matrizT[0][3] = 0;
//    matrizT[1][0] = 0; matrizT[1][1] = 1; matrizT[1][2] = 0; matrizT[0][3] = 0;
//    matrizT[2][0] = 0; matrizT[2][1] = 0; matrizT[2][2] = 1; matrizT[2][3] = 0;
//    matrizT[3][0] = -wcX; matrizT[3][1] = -wcY; matrizT[3][2] = -wcZ; matrizT[3][3] = 1;

//    for(it = pontosPPC.begin(); it != pontosPPC.end(); it++){
//        (*it)->transformar(matrizT);
//    }

//    teta = -teta*M_PI/180;

//    cosTeta = cos(teta);
//    sinTeta = sin(teta);

    //Rotaciona na direção contrária da window para o PPC
//    matrizT[0][0] = cosTeta + ux*ux*(1-cosTeta);    matrizT[0][1] = ux*uy*(1-cosTeta) - uz*sinTeta; matrizT[0][2] = ux*uz*(1-cosTeta) + uy*sinTeta; matrizT[0][3] = 0;
//    matrizT[1][0] = uy*ux*(1-cosTeta) + uz*sinTeta; matrizT[1][1] = cosTeta + uy*uy*(1-cosTeta);    matrizT[1][2] = uy*uz*(1-cosTeta) - ux*sinTeta; matrizT[1][3] = 0;
//    matrizT[2][0] = uz*ux*(1-cosTeta) - uy*sinTeta; matrizT[2][1] = uz*uy*(1-cosTeta) + ux*sinTeta; matrizT[2][2] = cosTeta + uz*uz*(1-cosTeta);    matrizT[2][3] = 0;
//    matrizT[3][0] = pX*(1-matrizT[0][0]) - pY*matrizT[1][0] - pZ*matrizT[2][0];	matrizT[3][1] = -pX*matrizT[0][1] + pY*(1-matrizT[1][1]) - pZ*matrizT[2][1];
//    matrizT[3][2] = -pX*matrizT[0][2] - pY*matrizT[1][2] + pZ*(1-matrizT[2][2]); matrizT[3][3] = 1;

//    for(it = pontosPPC.begin(); it != pontosPPC.end(); it++){
//        (*it)->transformar(matrizT);
//    }

//    matrizT[0][0] = 1; matrizT[0][1] = 0; matrizT[0][2] = 0;
//    matrizT[1][0] = 0; matrizT[1][1] = 1; matrizT[1][2] = 0;
//    matrizT[2][0] = -wcX; matrizT[2][1] = -wcY; matrizT[2][2] = 1;
//
//    for(it = pontosPPC.begin(); it != pontosPPC.end(); it++){
//        (*it)->transformar2D(matrizT);
//    }
/*
    teta = -teta*M_PI/180;

    matrizT[0][0] = cos(teta); matrizT[0][1] = -sin(teta); matrizT[0][2] = 0;
    matrizT[1][0] = sin(teta); matrizT[1][1] = cos(teta); matrizT[1][2] = 0;
    matrizT[2][0] = -cos(teta)*wcX - sin(teta)*wcY; matrizT[2][1] = -cos(teta)*wcY + sin(teta)*wcX; matrizT[2][2] = 1;*/
//    matrizT[0][0] = cos(teta); matrizT[0][1] = -sin(teta); matrizT[0][2] = 0;
//    matrizT[1][0] = sin(teta); matrizT[1][1] = cos(teta); matrizT[1][2] = 0;
//    matrizT[2][0] = xMedio*(1-cos(teta)) - yMedio*sin(teta); matrizT[2][1] = yMedio*(1-cos(teta)) + xMedio*sin(teta); matrizT[2][2] = 1;

    /*for(it = pontosPPC.begin(); it != pontosPPC.end(); it++){
        (*it)->transformar(matrizT);
    }*/
}

void Figura::teste(Ponto vX, Ponto vY, Ponto vZ, Ponto centro)
{
    matrizT[0][0] = vX.obterX(); matrizT[0][1] = vY.obterX(); matrizT[0][2] = vZ.obterX(); matrizT[0][3] = 0;
    matrizT[1][0] = vX.obterY(); matrizT[1][1] = vY.obterY(); matrizT[1][2] = vZ.obterY(); matrizT[0][3] = 0;
    matrizT[2][0] = vX.obterZ(); matrizT[2][1] = vY.obterZ(); matrizT[2][2] = vZ.obterZ(); matrizT[2][3] = 0;
    matrizT[3][0] = centro.obterX(); matrizT[3][1] = centro.obterY(); matrizT[3][2] = centro.obterZ(); matrizT[3][3] = 1;

    list<Ponto*>::iterator it;
    for(it = pontosPPC.begin(); it != pontosPPC.end(); it++){
        (*it)->transformar(matrizT);
    }
}

Ponto Figura::obterCentro(){
    double xSum = 0, ySum = 0, zSum = 0;
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        xSum += (*it)->obterX();
        ySum += (*it)->obterY();
        zSum += (*it)->obterZ();
    }
    double xMedio = xSum/pontos.size();
    double yMedio = ySum/pontos.size();
    double zMedio = zSum/pontos.size();
    return Ponto(xMedio, yMedio, zMedio);
}
