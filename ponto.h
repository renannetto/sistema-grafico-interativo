#ifndef PONTO_H
#define PONTO_H

class Ponto
{
public:
    Ponto(double vX, double vY);
    ~Ponto();
    double obterX() const;
    double obterY() const;
    void setarX(double);
    void setarY(double);
    void transformar2D(double**);
    bool operator==(Ponto);
private:
    double x;
    double y;
};

#endif // PONTO_H
