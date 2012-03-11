#ifndef WINDOWVIEWPORT_H
#define WINDOWVIEWPORT_H

#include "displayfile.h"
#include "window.h"

class WindowViewport
{
public:
    WindowViewport();
    string addFigure(Tipo tipo, list<Ponto*> pontos);
    void zoomIn();
    void zoomOut();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    double fx(double x);
    double fy(double y);
private:
    DisplayFile *displayFile;
    Window *window;
};

#endif // WINDOWVIEWPORT_H
