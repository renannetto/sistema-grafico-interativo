#include "windowviewport.h"

WindowViewport::WindowViewport()
{
    displayFile = new DisplayFile();
    window = new Window();
}

WindowViewport::~WindowViewport(){
    delete window;
    delete displayFile;
}

string WindowViewport::addFigure(Tipo tipo, list<Ponto*> pontos)
{
    return displayFile->addFigure(tipo, pontos);
}

list<Figura*> WindowViewport::getFigures(){
    return displayFile->getFigures();
}

void WindowViewport::destructFigure(string nome){
    displayFile->destructFigure(nome);
}

void WindowViewport::zoomIn(int percent)
{
    window->zoomIn(percent);
}

void WindowViewport::zoomOut(int percent)
{
    window->zoomOut(percent);
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
