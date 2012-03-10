#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    newObjectWindow = new Dialog(this);
    newObjectWindow->setVisible(false);
    viewport = new QGraphicsScene(0,0,640,480);
    ui->graphicsView->setScene(viewport);
    xMin = 0;
    yMin = 0;
    xMax = 640;
    yMax = 480;
    drawDot(200,200);
    drawLine(50, 50, 400, 200);
    drawLine(0,0,640,480);
    drawLine(600,240,800,480);
    for(int i = 0; i < 150; i++){
        moveLeft();
    }
    viewport->clear();
    drawDot(200,200);
    drawLine(50, 50, 400, 200);
    drawLine(0,0,640,480);
    drawLine(600,240,800,480);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::abrirJanela(){
    newObjectWindow->setVisible(true);
}

void MainWindow::drawDot(double x, double y){
    x = fx(x);
    y = fy(y);
    viewport->addLine(x,y,x,y);
}

void MainWindow::drawLine(double x1, double y1, double x2, double y2){
    viewport->addLine(fx(x1),fy(y1),fx(x2),fy(y2));
}

qreal MainWindow::fx(double x){
    return (x - xMin) * 640 / (xMax - xMin);
}

qreal MainWindow::fy(double y){
    return (yMax - y) * 480 / (yMax - yMin);
}

void MainWindow::zoomIn(){
    xMin++;
    yMin++;
    xMax--;
    yMax--;
}

void MainWindow::zoomOut(){
    xMin--;
    yMin--;
    xMax++;
    yMax++;
}

void MainWindow::moveLeft(){
    xMin--;
    xMax--;
}

void MainWindow::moveRight(){
    xMin++;
    xMax++;
}

void MainWindow::moveDown(){
    yMin--;
    yMax--;
}

void MainWindow::moveUp(){
    yMin++;
    yMax++;
}
