#include "figura.h"

Figura::Figura(string vNome, Tipo vTipo, list<Ponto *> vPontos)
{
    nome = vNome;
    tipo = vTipo;
    pontos = vPontos;
}

Figura::~Figura()
{
}

list<Ponto*> Figura::getPontos(){
    return pontos;
}
