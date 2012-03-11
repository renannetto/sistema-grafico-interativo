#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    windowViewport = new WindowViewport();

    ui->setupUi(this);

    newObjectWindow = new Dialog(this); newObjectWindow->setVisible(false);
    connect(newObjectWindow, SIGNAL(drawLineM(double, double, double, double)),
    this, SLOT(drawLine(double, double, double, double)));
    connect(newObjectWindow, SIGNAL(drawDotM(double, double)),
    this, SLOT(drawDot(double, double)));
    connect(newObjectWindow, SIGNAL(drawPolygonM(list<Ponto*>)), this, SLOT(drawPolygon(list<Ponto*>)));

    viewport = new QGraphicsScene(0,0,VIEWPORTXSIZE,VIEWPORTYSIZE);
    ui->graphicsView->setScene(viewport);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::abrirJanela(){
    newObjectWindow->setVisible(true);
}

void MainWindow::drawDot(double x, double y){
    list<Ponto*> pontos;
    pontos.push_back(new Ponto(x, y));
    windowViewport->addFigure(pontos);
    x = windowViewport->fx(x);
    y = windowViewport->fy(y);
    viewport->addLine(x,y,x,y);
}

void MainWindow::drawLine(double x1, double y1, double x2, double y2){
    list<Ponto*> pontos;
    pontos.push_back(new Ponto(x1, y1));
    pontos.push_back(new Ponto(x2, y2));
    windowViewport->addFigure(pontos);
    viewport->addLine(windowViewport->fx(x1),windowViewport->fy(y1),windowViewport->fx(x2),windowViewport->fy(y2));
}

void MainWindow::drawPolygon(list<Ponto *> pontos){
    windowViewport->addFigure(pontos);
    QPolygonF poligono;
    int size = pontos.size();
    for (int i=0; i<size; i++) {
        poligono << QPointF(windowViewport->fx(pontos.front()->getX()), windowViewport->fy(pontos.front()->getY()));
        pontos.pop_front();
    }
    viewport->addPolygon(poligono);
}

void MainWindow::zoomIn(){
    windowViewport->zoomIn();
}

void MainWindow::zoomOut(){
    windowViewport->zoomOut();
}

void MainWindow::moveLeft(){
    windowViewport->moveLeft();
}

void MainWindow::moveRight(){
    windowViewport->moveRight();
}

void MainWindow::moveDown(){
   windowViewport->moveDown();
}

void MainWindow::moveUp(){
    windowViewport->moveUp();
}
