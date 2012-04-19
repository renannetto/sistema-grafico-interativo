#ifndef PONTO_H
#define PONTO_H

class Ponto
{
public:
    Ponto(double vX, double vY, double vZ = 0);
    ~Ponto();
    double obterX() const;
    double obterY() const;
    double obterZ() const;
    void setarX(double);
    void setarY(double);
    void setarZ(double);
    void transformar(double**);
    bool operator==(Ponto);
private:
    double x;
    double y;
    double z;
};

#endif // PONTO_H
