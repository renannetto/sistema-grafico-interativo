#ifndef PONTO_H
#define PONTO_H

class Ponto
{
public:
    Ponto(double vX, double vY);
    ~Ponto();
    void setX(double);
    void setY(double);
private:
    double x;
    double y;
};

#endif // PONTO_H
