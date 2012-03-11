#ifndef PONTO_H
#define PONTO_H

class Ponto
{
public:
    Ponto(double vX, double vY);
    ~Ponto();
    double getX();
    double getY();
private:
    double x;
    double y;
};

#endif // PONTO_H
