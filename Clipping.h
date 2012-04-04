#ifndef CLIPPING_H
#define CLIPPING_H

#include <ponto.h>

class Clipping
{
    enum RC {
        M = 0x0,
        B = 0x4,
        C = 0x8,
        E = 0x1,
        D = 0x2,
        CE = 0x9,
        CD = 0x10,
        BE = 0x5,
        BD = 0x6
    };
public:
    Clipping(double,double,double,double);
    int identificarRC(Ponto const &);
    bool clippingDePonto(Ponto&);
    bool clippingDeLinhaCohen(Ponto const &, Ponto const &, Ponto&, Ponto&);
    bool clippingDePoligonosWeiler();
private:
    double xMin;
    double xMax;
    double yMin;
    double yMax;
};

#endif // CLIPPING_H
