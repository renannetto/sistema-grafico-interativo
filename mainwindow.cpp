#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start(){
    ui->setupUi(this);

    newObjectWindow = new Dialog(this);
    newObjectWindow->setVisible(false);
    viewport = new QGraphicsScene(0,0,VIEWPORTXSIZE,VIEWPORTYSIZE);
    ui->graphicsView->setScene(viewport);
    windowViewport = new WindowViewport();

    connect(newObjectWindow, SIGNAL(drawFigure(Tipo, list<Ponto*>)),
    this, SLOT(constructFigure(Tipo, list<Ponto*>)));
}

void MainWindow::restart(){
    delete newObjectWindow;
    delete windowViewport;
    delete viewport;

    start();
}

void MainWindow::abrirJanela(){
    newObjectWindow->setVisible(true);
}

void MainWindow::constructFigure(Tipo tipo, list<Ponto *> pontos){
    QString nome = QString::fromStdString(windowViewport->addFigure(tipo, pontos));
    ui->listWidget->addItem(nome);
    drawFigures();
}

void MainWindow::destructFigure(){
    string nome = ui->listWidget->currentItem()->text().toStdString();
    if (nome != "Novo Objeto"){
        ui->listWidget->currentItem()->~QListWidgetItem();
        windowViewport->destructFigure(nome);
        drawFigures();
        cout << "Figura apagada : " << nome << endl;
   }
}

void MainWindow::drawFigures() {
    viewport->clear();
    list<Figura*> figuras = windowViewport->getFigures();
    list<Ponto*> pontos;
    for (int i = 0; i < figuras.size(); i++){
        Figura* figura = figuras.back();
        pontos = figura->getPontos();
        if(pontos.size()==1){
            int x = windowViewport->fx(pontos.front()->getX());
            int y = windowViewport->fy(pontos.front()->getY());
            viewport->addLine(x,y,x,y);
        } else{
            QPolygonF poligono;
            int size = pontos.size();
            for (int i=0; i<size; i++) {
                Ponto* ponto = pontos.front();
                poligono << QPointF(windowViewport->fx(ponto->getX()), windowViewport->fy(ponto->getY()));
                pontos.pop_front();
                pontos.push_back(ponto);
            }
            viewport->addPolygon(poligono);
        }
        figuras.pop_back();
        figuras.push_front(figura);
    }
}

void MainWindow::zoomIn(){
    windowViewport->zoomIn(ui->horizontalSlider->sliderPosition());
    drawFigures();
}

void MainWindow::zoomOut(){
    windowViewport->zoomOut(ui->horizontalSlider->sliderPosition());
    drawFigures();
}

void MainWindow::showZoomPower(int zoomValue){
    string aux;
    ui->textBrowser_2->clear();
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
