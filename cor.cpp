#include "cor.h"

Cor::Cor(int vermelho, int verde, int azul)
{
    this->vermelho = vermelho;
    this->verde = verde;
    this->azul = azul;
}

int Cor::obterVermelho() {
    return vermelho;
}

int Cor::obterVerde() {
    return verde;
}

int Cor::obterAzul() {
    return azul;
}
