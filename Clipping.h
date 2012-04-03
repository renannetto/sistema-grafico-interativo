#ifndef CLIPPING_H
#define CLIPPING_H

#include <ponto.h>

class Clipping
{
public:
    Clipping(double,double,double,double);
    bool clippingDePonto(Ponto&);
    bool clippingDeLinhaCohen(const Ponto&, const Ponto&, Ponto&, Ponto&);
    bool clippingDePoligonosWeiler();
private:
    double xMin;
    double xMax;
    double yMin;
    double yMax;
};

#endif // CLIPPING_H
