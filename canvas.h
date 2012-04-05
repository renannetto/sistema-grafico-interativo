#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>
#include <iostream>
#include "mainwindow.h"
#include <QWheelEvent>

using namespace std;

class MainWindow;
class Canvas : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = 0);
    void fixarJanelaPrincipal(QMainWindow * janelaPrincipal);

private:
    MainWindow * janelaPrincipal;
    typedef enum Teclas {
        CIMA = 16777235, BAIXO = 16777237, ESQUERDA = 16777234,  DIREITA = 16777236,
        MAIS = 43, MENOS = 45, GIRARDIREITA = 48, GIRARESQUERDA = 57, CTRL = 16777249,
        SHIFT = 16777248
    } Tecla;
    bool ctrlAtivado;
    bool shiftAtivado;

protected:
    virtual void mouseReleaseEvent (QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void wheelEvent(QWheelEvent *event);


public slots:

};

#endif // CANVAS_H
