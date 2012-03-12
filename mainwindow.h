#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <string>
#include <iostream>
#include "dialog.h"
#include "windowviewport.h"


namespace Ui {
    class MainWindow;
}

using namespace std;

static double const VIEWPORTXSIZE = 640;
static double const VIEWPORTYSIZE = 480;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void abrirJanela();
    void constructFigure(Tipo, list<Ponto*>);
    void destructFigure();
    void drawFigures();
    void zoomIn();
    void zoomOut();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

private:
    WindowViewport *windowViewport;
    Ui::MainWindow *ui;
    Dialog *newObjectWindow;
    QGraphicsScene * viewport;
};

#endif // MAINWINDOW_H
