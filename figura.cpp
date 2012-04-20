#include "figura.h"

Figura::Figura(string vNome, Tipo vTipo, list<Ponto *> vPontos, Cor vCor, double wcX, double wcY, double teta)
    : cor(vCor)
{
    nome = vNome;
    tipo = vTipo;
    pontos = vPontos;

    pontosPPC = pontos;

    matrizT = new double*[4];
    for(int i = 0; i < 4; i++)
        matrizT[i] = new double[4];

    gerarDescricaoPPC(wcX, wcY, teta);
}

Figura::~Figura()
{
}

list<Ponto*> Figura::obterPontos(){
    return pontos;
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

void Figura::transladar(double vX, double vY) {
    double vZ = 0;
    matrizT[0][0] = 1; matrizT[0][1] = 0; matrizT[0][2] = 0; matrizT[0][3] = 0;
    matrizT[1][0] = 0; matrizT[1][1] = 1; matrizT[1][2] = 0; matrizT[0][3] = 0;
    matrizT[2][0] = 0; matrizT[2][1] = 0; matrizT[2][2] = 1; matrizT[2][3] = 0;
    matrizT[3][0] = vX; matrizT[3][1] = vY; matrizT[3][2] = vZ; matrizT[3][3] = 1;
    transformar();
}

void Figura::escalonar(double vX, double vY){
    Ponto centro = obterCentro();
    double xMedio = centro.obterX();
    double yMedio = centro.obterY();
    double zMedio = centro.obterZ();

    double vZ = 0;

    matrizT[0][0] = vX; matrizT[0][1] = 0; matrizT[0][2] = 0; matrizT[0][3] = 0;
    matrizT[1][0] = 0; matrizT[1][1] = vY; matrizT[1][2] = 0; matrizT[1][3] = 0;
    matrizT[2][0] = 0; matrizT[2][1] = 0; matrizT[2][2] = vZ; matrizT[2][3] = 0;
    matrizT[3][0] = xMedio*(1-vX); matrizT[3][1] = yMedio*(1-vY); matrizT[3][2] = zMedio*(1-vZ); matrizT[3][3] = 1;
    transformar();
}

void Figura::rotacionarNaOrigem2D(double teta) {
    Ponto vetor(0, 0, 1);
    double ux = vetor.obterX();
    double uy = vetor.obterY();
    double uz = vetor.obterZ();

    teta = teta*M_PI/180;

    double cosTeta = cos(teta);
    double sinTeta = sin(teta);

    matrizT[0][0] = cosTeta + ux*ux*(1-cosTeta); matrizT[0][1] = ux*uy*(1-cosTeta) - uz*sinTeta; matrizT[0][2] = ux*uz*(1-cosTeta) + uy*sinTeta; matrizT[0][3] = 0;
    matrizT[1][0] = uy*ux*(1-cosTeta) + uz*sinTeta; matrizT[1][1] = cosTeta + uy*uy*(1-cosTeta); matrizT[1][2] = uy*uz*(1-cosTeta) - ux*sinTeta; matrizT[1][3] = 0;
    matrizT[2][0] = uz*ux*(1-cosTeta) - uy*sinTeta; matrizT[2][1] = uz*uy*(1-cosTeta) + ux*sinTeta; matrizT[2][2] = cosTeta + uz*uz*(1-cosTeta); matrizT[2][3] = 0;
    matrizT[3][0] = 0; matrizT[3][1] = 0; matrizT[3][2] = 0; matrizT[3][3] = 1;
    transformar();
}

/*void Figura::rotacionarNaOrigem2D(double teta){
    teta = teta*M_PI/180;
    matrizT[0][0] = cos(teta); matrizT[0][1] = -sin(teta); matrizT[0][2] = 0;
    matrizT[1][0] = sin(teta); matrizT[1][1] = cos(teta); matrizT[1][2] = 0;
    matrizT[2][0] = 0; matrizT[2][1] = 0; matrizT[2][2] = 1;
    transformar();
}*/

void Figura::rotacionarNoCentro2D(double teta){
    Ponto centro = obterCentro();
    double xMedio = centro.obterX();
    double yMedio = centro.obterY();

    teta = teta*M_PI/180;
    matrizT[0][0] = cos(teta); matrizT[0][1] = -sin(teta); matrizT[0][2] = 0;
    matrizT[1][0] = sin(teta); matrizT[1][1] = cos(teta); matrizT[1][2] = 0;
    matrizT[2][0] = xMedio*(1-cos(teta)) - yMedio*sin(teta); matrizT[2][1] = yMedio*(1-cos(teta)) + xMedio*sin(teta); matrizT[2][2] = 1;
    transformar();
}

void Figura::rotacionarNoPonto2D(double teta, double pX, double pY){
    teta = teta*M_PI/180;
    matrizT[0][0] = cos(teta); matrizT[0][1] = -sin(teta); matrizT[0][2] = 0;
    matrizT[1][0] = sin(teta); matrizT[1][1] = cos(teta); matrizT[1][2] = 0;
    matrizT[2][0] = pX*(1-cos(teta)) - pY*sin(teta); matrizT[2][1] = pY*(1-cos(teta)) + pX*sin(teta); matrizT[2][2] = 1;
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

void Figura::gerarDescricaoPPC(double wcX, double wcY, double teta){
    list<Ponto*>::iterator it;

    for (it = pontos.begin(); it != pontos.end(); it++){
        pontosPPC.pop_front();
        pontosPPC.push_back(new Ponto((*it)->obterX(), (*it)->obterY()));
    }

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

    transladar(-wcX, -wcY);
}

Ponto Figura::obterCentro(){
    double xSum = 0, ySum = 0;
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        xSum += (*it)->obterX();
        ySum += (*it)->obterY();
    }
    double xMedio = xSum/pontos.size();
    double yMedio = ySum/pontos.size();
    return Ponto(xMedio, yMedio);
}
