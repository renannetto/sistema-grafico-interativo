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
    ui->graphicsView;
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

void MainWindow::drawDot(int x, int y){
    viewport->addLine(x,y,x,y);
}

void MainWindow::drawLine(int x1, int y1, int x2, int y2){
    viewport->addLine(x1,y1,x2,y2);
}
