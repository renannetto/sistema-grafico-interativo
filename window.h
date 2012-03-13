#ifndef WINDOW_H
#define WINDOW_H

class Window
{
public:
    Window();
    void zoomIn(int);
    void zoomOut(int);
    void moverParaEsquerda();
    void moverParaDireita();
    void moverParaCima();
    void moverParaBaixo();
    double fx(double x);
    double fy(double y);
private:
    double xMin;
    double xMax;
    double yMin;
    double yMax;
};

#endif // WINDOW_H
