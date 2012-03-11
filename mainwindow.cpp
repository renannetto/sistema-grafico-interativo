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
    QString nome = QString::fromStdString(windowViewport->addFigure(PONTO, pontos));
    x = windowViewport->fx(x);
    y = windowViewport->fy(y);
    viewport->addLine(x,y,x,y);
    ui->listWidget->addItem(nome);
}

void MainWindow::drawLine(double x1, double y1, double x2, double y2){
    list<Ponto*> pontos;
    pontos.push_back(new Ponto(x1, y1));
    pontos.push_back(new Ponto(x2, y2));
    QString nome = QString::fromStdString(windowViewport->addFigure(RETA, pontos));
    viewport->addLine(windowViewport->fx(x1),windowViewport->fy(y1),windowViewport->fx(x2),windowViewport->fy(y2));
    ui->listWidget->addItem(nome);
}

void MainWindow::drawPolygon(list<Ponto *> pontos){
    QString nome = QString::fromStdString(windowViewport->addFigure(POLIGONO, pontos));
    QPolygonF poligono;
    int size = pontos.size();
    for (int i=0; i<size; i++) {
        poligono << QPointF(windowViewport->fx(pontos.front()->getX()), windowViewport->fy(pontos.front()->getY()));
        pontos.pop_front();
    }
    viewport->addPolygon(poligono);
    ui->listWidget->addItem(nome);
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
