#ifndef FACE_H
#define FACE_H

#include <list>
#include "ponto.h"

using namespace std;

class Face
{
public:
    Face(int vPonto1, int vPonto2, int vPonto3);
    ~Face();
    int* obterPontos();
private:
    int ponto1;
    int ponto2;
    int ponto3;
};

#endif // FACE_H
