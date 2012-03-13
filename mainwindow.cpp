#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    iniciar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniciar(){
    ui->setupUi(this);

    newObjectWindow = new Dialog(this);
    newObjectWindow->setVisible(false);
    viewport = new QGraphicsScene(0,0,VIEWPORTXSIZE,VIEWPORTYSIZE);
    ui->graphicsView->setScene(viewport);
    windowViewport = new WindowViewport();
    ui->zoomText->clear();
    mostrarValorDoZoom(ui->zoomSlider->value());

    connect(newObjectWindow, SIGNAL(drawFigure(Tipo, list<Ponto*>)),
    this, SLOT(construirFigura(Tipo, list<Ponto*>)));
}

void MainWindow::reiniciar(){
    delete newObjectWindow;
    delete windowViewport;
    delete viewport;

    iniciar();
}

void MainWindow::abrirJanela(){
    newObjectWindow->setVisible(true);
}

void MainWindow::construirFigura(Tipo tipo, list<Ponto *> pontos){
    QString nome = QString::fromStdString(windowViewport->addFigure(tipo, pontos));
    ui->listaObjetos->addItem(nome);
    desenharFiguras();
}

void MainWindow::destruirFigura(){
    string nome = ui->listaObjetos->currentItem()->text().toStdString();
    if (nome != "Novo Objeto"){
        ui->listaObjetos->currentItem()->~QListWidgetItem();
        windowViewport->destructFigure(nome);
        desenharFiguras();
        cout << "Figura apagada : " << nome << endl;
   }
}

void MainWindow::desenharFiguras() {
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
    windowViewport->zoomIn(ui->zoomSlider->sliderPosition());
    desenharFiguras();
}

void MainWindow::zoomOut(){
    windowViewport->zoomOut(ui->zoomSlider->sliderPosition());
    desenharFiguras();
}

void MainWindow::mostrarValorDoZoom(int zoomValue){
    stringstream ss;
    ss << zoomValue;
    ui->zoomText->clear();
    ui->zoomText->setText(QString::fromStdString(ss.str()));
}

void MainWindow::moveLeft(){
    windowViewport->moveLeft();
    desenharFiguras();
}

void MainWindow::moveRight(){
    windowViewport->moveRight();
    desenharFiguras();
}

void MainWindow::moveDown(){
    windowViewport->moveDown();
    desenharFiguras();
}

void MainWindow::moveUp(){
    windowViewport->moveUp();
    desenharFiguras();
}
