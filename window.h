#ifndef WINDOW_H
#define WINDOW_H

class Window
{
public:
    Window();
    void resetarCoordenadas();
    void zoomIn(int);
    void zoomOut(int);
    void moverParaEsquerda();
    void moverParaDireita();
    void moverParaCima();
    void moverParaBaixo();
    double obterXMinDaWindow();
    double obterYMinDaWindow();
    double obterXMaxDaWindow();
    double obterYMaxDaWindow();
private:
    double xMin;
    double xMax;
    double yMin;
    double yMax;
};

#endif // WINDOW_H
