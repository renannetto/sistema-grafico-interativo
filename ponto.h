#ifndef PONTO_H
#define PONTO_H

class Ponto
{
public:
    Ponto(double vX, double vY);
    ~Ponto();
    double obterX();
    double obterY();
    void transformar2D(double**);
private:
    double x;
    double y;
};

#endif // PONTO_H
