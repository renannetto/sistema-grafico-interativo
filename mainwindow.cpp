#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    newObjectWindow = new Dialog(this); newObjectWindow->setVisible(false);
    connect(newObjectWindow, SIGNAL(drawLineM(double, double, double, double)),
    this, SLOT(drawLine(double, double, double, double)));
    connect(newObjectWindow, SIGNAL(drawDotM(double, double)),
    this, SLOT(drawDot(double, double)));

    viewport = new QGraphicsScene(0,0,VIEWPORTXSIZE,VIEWPORTYSIZE);
    ui->graphicsView->setScene(viewport);

    xMin = 0;
    yMin = 0;
    xMax = 640;
    yMax = 480;
    //drawObjects();
//    for(int i = 0; i < 150; i++){
//        moveLeft();
//    }
//    viewport->clear();
//    drawDot(200,200);
//    drawLine(50, 50, 400, 200);
//    drawLine(0,0,640,480);
//    drawLine(600,240,800,480);
//    for(int i = 0; i < 250; i++){
//        zoomIn();
//    }
//    viewport->clear();
//    drawDot(200,200);
//    drawLine(50, 50, 400, 200);
//    drawLine(0,0,640,480);
//    drawLine(600,240,800,480);
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

void MainWindow::drawObjects(){
    viewport->clear();
    drawDot(200,200);
    drawLine(50, 50, 400, 200);
    drawLine(0,0,640,480);
    drawLine(600,240,800,480);
}

qreal MainWindow::fx(double x){
    return (x - xMin) * 640 / (xMax - xMin);
}

qreal MainWindow::fy(double y){
    return (yMax - y) * 480 / (yMax - yMin);
}

void MainWindow::zoomIn(){
    xMin += 2.5;
    yMin += 2.5;
    xMax -= 2.5;
    yMax -= 2.5;
    drawObjects();
}

void MainWindow::zoomOut(){
    xMin -= 2.5;
    yMin -= 2.5;
    xMax += 2.5;
    yMax += 2.5;
    drawObjects();
}

void MainWindow::moveLeft(){
    xMin -= 5;
    xMax -= 5;
    drawObjects();
}

void MainWindow::moveRight(){
    xMin += 5;
    xMax += 5;
    drawObjects();
}

void MainWindow::moveDown(){
    yMin -= 5;
    yMax -= 5;
    drawObjects();
}

void MainWindow::moveUp(){
    yMin += 5;
    yMax += 5;
    drawObjects();
}
