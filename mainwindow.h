#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "dialog.h"
#include "windowviewport.h"

namespace Ui {
    class MainWindow;
}

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
    void drawDot(double x, double y);
    void drawLine(double x1, double y1, double x2, double y2);
    void drawPolygon(list<Ponto*> pontos);
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
