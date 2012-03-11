#include "figura.h"

Figura::Figura(list<Ponto*> vPontos)
{
    pontos = vPontos;
}

Figura::~Figura()
{
}

list<Ponto*> Figura::getPontos(){
    return pontos;
}
