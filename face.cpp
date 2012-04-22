#include "face.h"

Face::Face(int vPonto1, int vPonto2, int vPonto3)
{
    ponto1 = vPonto1;
    ponto2 = vPonto2;
    ponto3 = vPonto3;
}

Face::~Face() {
}

int* Face::obterPontos() {
    int *pontos = new int[3];
    pontos[0] = ponto1;
    pontos[1] = ponto2;
    pontos[2] = ponto3;
    return pontos;
}
