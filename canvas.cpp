#include "canvas.h"

Canvas::Canvas(QWidget *parent) : QGraphicsView(parent)
{
    ctrlAtivado = false;
    shiftAtivado = false;
    clicado = false;
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
//    this->janelaPrincipal->arrastarCamera(event->x(),event->y());
    clicado = false;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    this->janelaPrincipal->receberPonto(event->x(), event->y());
    clicado = true;
}

void Canvas::mouseMoveEvent(QMouseEvent *event){
    if(clicado){
        this->janelaPrincipal->arrastarCamera(event->x(),event->y());
    }
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
    case CTRL:
        ctrlAtivado = true;
        break;
    case SHIFT:
        shiftAtivado = true;
        break;
    }
}

void Canvas::keyReleaseEvent(QKeyEvent *event){
    int tecla = event->key();

    switch(tecla) {
    case CTRL:
        ctrlAtivado = false;
        break;
    case SHIFT:
        shiftAtivado = false;
        break;
    }
}

void Canvas::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
        if(ctrlAtivado)
            this->janelaPrincipal->aumentarRegiaoDeClipping();
        else if (shiftAtivado)
            this->janelaPrincipal->rotacionarWindowParaDireita();
        else
            this->janelaPrincipal->zoomIn();
    else if (event-> delta() < 0)
        if(ctrlAtivado)
            this->janelaPrincipal->diminuirRegiaoDeClipping();
        else if (shiftAtivado)
            this->janelaPrincipal->rotacionarWindowParaEsquerda();
        else
            this->janelaPrincipal->zoomOut();
}
