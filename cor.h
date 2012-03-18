#ifndef COR_H
#define COR_H

class Cor
{
public:
    Cor(int, int, int);
    int obterVermelho();
    int obterVerde();
    int obterAzul();
private:
    int vermelho;
    int verde;
    int azul;
};

#endif // COR_H
