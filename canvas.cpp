#include "canvas.h"

Canvas::Canvas(QWidget *parent) : QGraphicsView(parent)
{
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    this->janelaPrincipal->receberPonto(event->x(), event->y());
}

void Canvas::fixarJanelaPrincipal(QMainWindow *janelaPrincipal)
{
    this->janelaPrincipal = (MainWindow*) janelaPrincipal;
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
    int tecla;

    tecla = event->key();

    switch(tecla) {

    case CIMA:
        this->janelaPrincipal->moverParaCima();
        break;
    case BAIXO:
        this->janelaPrincipal->moverParaBaixo();
        break;
    case ESQUERDA:
        this->janelaPrincipal->moverParaEsquerda();
        break;
    case DIREITA:
        this->janelaPrincipal->moverParaDireita();
        break;
    case MAIS:
        this->janelaPrincipal->zoomIn();
        break;
    case MENOS:
        this->janelaPrincipal->zoomOut();
        break;
    case GIRARDIREITA:
        this->janelaPrincipal->rotacionarWindowParaDireita();
        break;
    case GIRARESQUERDA:
        this->janelaPrincipal->rotacionarWindowParaEsquerda();
        break;
    }
}

void Canvas::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
        this->janelaPrincipal->zoomIn();
    else if (event-> delta() < 0)
        this->janelaPrincipal->zoomOut();
}
