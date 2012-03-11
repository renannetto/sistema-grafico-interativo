#include "windowviewport.h"

WindowViewport::WindowViewport()
{
    displayFile = new DisplayFile();
    window = new Window();
}

void WindowViewport::addFigure(list<Ponto*> pontos)
{
    displayFile->addFigure(pontos);
}

list<Figura*> WindowViewport::getFigures(){
    return displayFile->getFigures();
}

void WindowViewport::zoomIn()
{
    window->zoomIn();
}

void WindowViewport::zoomOut()
{
    window->zoomOut();
}

void WindowViewport::moveLeft()
{
    window->moveLeft();
}

void WindowViewport::moveRight()
{
    window->moveRight();
}

void WindowViewport::moveDown()
{
    window->moveDown();
}

void WindowViewport::moveUp()
{
    window->moveUp();
}

double WindowViewport::fx(double x)
{
    return window->fx(x);
}

double WindowViewport::fy(double y)
{
    return window->fy(y);
}
