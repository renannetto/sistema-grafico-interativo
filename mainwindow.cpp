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

    connect(newObjectWindow, SIGNAL(desenharFigura(Tipo, list<Ponto*>)),
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
    QString nome = QString::fromStdString(windowViewport->adicionarFigura(tipo, pontos));
    ui->listaObjetos->addItem(nome);
    desenharFiguras();
}

void MainWindow::destruirFigura(){
    string nome = ui->listaObjetos->currentItem()->text().toStdString();
    if (nome != "Novo Objeto"){
        ui->listaObjetos->currentItem()->~QListWidgetItem();
        windowViewport->destruirFigura(nome);
        desenharFiguras();
        cout << "Figura apagada : " << nome << endl;
   }
}

void MainWindow::desenharFiguras() {
    viewport->clear();
    list<Figura*> figuras = windowViewport->obterFiguras();
    list<Ponto*> pontos;
    for (int i = 0; i < figuras.size(); i++){
        Figura* figura = figuras.back();
        pontos = figura->obterPontos();
        if(pontos.size()==1){
            int x = windowViewport->fx(pontos.front()->obterX());
            int y = windowViewport->fy(pontos.front()->obterY());
            viewport->addLine(x,y,x,y);
        } else{
            QPolygonF poligono;
            int size = pontos.size();
            for (int i=0; i<size; i++) {
                Ponto* ponto = pontos.front();
                poligono << QPointF(windowViewport->fx(ponto->obterX()), windowViewport->fy(ponto->obterY()));
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

void MainWindow::moverParaEsquerda(){
    windowViewport->moverParaEsquerda();
    desenharFiguras();
}

void MainWindow::moverParaDireita(){
    windowViewport->moverParaDireita();
    desenharFiguras();
}

void MainWindow::moverParaBaixo(){
    windowViewport->moverParaBaixo();
    desenharFiguras();
}

void MainWindow::moverParaCima(){
    windowViewport->moverParaCima();
    desenharFiguras();
}
