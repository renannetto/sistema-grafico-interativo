#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    windowViewport = new WindowViewport();

    ui->setupUi(this);

    newObjectWindow = new Dialog(this);
    newObjectWindow->setVisible(false);
    connect(newObjectWindow, SIGNAL(drawLineM(list<Ponto*>)),
    this, SLOT(constructFigure(list<Ponto*>)));
    connect(newObjectWindow, SIGNAL(drawDotM(list<Ponto*>)),
    this, SLOT(constructFigure(list<Ponto*>)));
    connect(newObjectWindow, SIGNAL(drawPolygonM(list<Ponto*>)),
    this, SLOT(constructFigure(list<Ponto*>)));

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


void MainWindow::constructFigure(list<Ponto *> pontos){
    windowViewport->addFigure(PONTO, pontos);
    drawFigures();
}

void MainWindow::drawFigures() {
    viewport->clear();
    list<Figura*> figuras = windowViewport->getFigures();
    list<Ponto*> pontos;
    for (int i = 0; i < figuras.size(); i++){
        pontos = figuras.back()->getPontos();
        if(pontos.size()==1){
            int x = windowViewport->fx(pontos.front()->getX());
            int y = windowViewport->fy(pontos.front()->getY());
            viewport->addLine(x,y,x,y);
        } else{
            QPolygonF poligono;
            int size = pontos.size();
            for (int i=0; i<size; i++) {
                poligono << QPointF(windowViewport->fx(pontos.front()->getX()), windowViewport->fy(pontos.front()->getY()));
                pontos.pop_front();
            }
            viewport->addPolygon(poligono);
        }
        figuras.pop_back();
    }
}

void MainWindow::zoomIn(){
    windowViewport->zoomIn();
    drawFigures();
}

void MainWindow::zoomOut(){
    windowViewport->zoomOut();
    drawFigures();
}

void MainWindow::moveLeft(){
    windowViewport->moveLeft();
    drawFigures();
}

void MainWindow::moveRight(){
    windowViewport->moveRight();
    drawFigures();
}

void MainWindow::moveDown(){
    windowViewport->moveDown();
    drawFigures();
}

void MainWindow::moveUp(){
    windowViewport->moveUp();
    drawFigures();
}
