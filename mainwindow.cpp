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
    janelaDeTransformacoes = new Transformacoes(this);
    janelaDeTransformacoes->setVisible(false);
    viewport = new QGraphicsScene(0,0,VIEWPORTXSIZE,VIEWPORTYSIZE);
    ui->graphicsView->setScene(viewport);
    windowViewport = new WindowViewport();
    ui->zoomText->clear();
    mostrarValorDoZoom(ui->zoomSlider->value());

    connect(newObjectWindow, SIGNAL(desenharFigura(Tipo, list<Ponto*>, QColor)),
    this, SLOT(construirFigura(Tipo, list<Ponto*>, QColor)));
    connect(janelaDeTransformacoes, SIGNAL(sTransladar2D(double,double)),
    this, SLOT(transladar2D(double,double)));
    connect(janelaDeTransformacoes, SIGNAL(sEscalonar2D(double,double)),
    this, SLOT(escalonar2D(double,double)));
    connect(janelaDeTransformacoes, SIGNAL(sRotacionarNaOrigem(double)),
    this, SLOT(rotacionarNaOrigem2D(double)));
    connect(janelaDeTransformacoes, SIGNAL(sRotacionarNoCentro(double)),
    this, SLOT(rotacionarNoCentro2D(double)));
    connect(janelaDeTransformacoes, SIGNAL(sRotacionarNoPonto(double,double,double)),
    this, SLOT(rotacionarNoPonto2D(double,double,double)));
    connect(janelaDeTransformacoes, SIGNAL(sMudarCor(QColor)), this, SLOT(mudarCor(QColor)));

    desenharFiguras();
}

void MainWindow::reiniciar(){
    delete newObjectWindow;
    delete windowViewport;
    delete viewport;

    iniciar();
}

void MainWindow::resetarWindow(){
    windowViewport->resetarWindow();
    desenharFiguras();
}

void MainWindow::abrirJanela(){
    if(ui->listaObjetos->currentItem()->text().toStdString() == "Novo Objeto")
        newObjectWindow->setVisible(true);
    else
        janelaDeTransformacoes->setVisible(true);
}

void MainWindow::construirFigura(Tipo tipo, list<Ponto *> pontos, QColor cor){
    QString nome = QString::fromStdString(windowViewport->adicionarFigura(tipo, pontos, cor.red(), cor.green(), cor.blue()));
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

        Cor cor = figura->obterCor();

        QColor qCor = QColor::fromRgb(cor.obterVermelho(), cor.obterVerde(), cor.obterAzul());

        double xP,yP,xa,ya,x,y;
        xP = xa = windowViewport->fx(pontos.front()->obterX());
        yP = ya = windowViewport->fy(pontos.front()->obterY());

        list<Ponto*>::iterator it;
        for(it = pontos.begin(); it != pontos.end(); it++){
            x = windowViewport->fx((*it)->obterX());
            y = windowViewport->fy((*it)->obterY());
            viewport->addLine(xa,ya,x,y, QPen(qCor));
            xa = x;
            ya = y;
        }
        viewport->addLine(x,y,xP,yP, QPen(qCor));
//        if(pontos.size()==1){
//            int x = windowViewport->fx(pontos.front()->obterX());
//            int y = windowViewport->fy(pontos.front()->obterY());
//            viewport->addLine(x,y,x,y);
//        } else{
//            QPolygonF poligono;
//            int size = pontos.size();
//            for (int i=0; i<size; i++) {
//                Ponto* ponto = pontos.front();
//                poligono << QPointF(windowViewport->fx(ponto->obterX()), windowViewport->fy(ponto->obterY()));
//                pontos.pop_front();
//                pontos.push_back(ponto);
//            }
//            viewport->addPolygon(poligono);
//        }
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

void MainWindow::transladar2D(double vX, double vY){
    windowViewport->transladar2D(ui->listaObjetos->currentItem()->text().toStdString(),vX,vY);
    desenharFiguras();
}

void MainWindow::escalonar2D(double vX, double vY){
    windowViewport->escalonar2D(ui->listaObjetos->currentItem()->text().toStdString(),vX,vY);
    desenharFiguras();
}

void MainWindow::rotacionarNaOrigem2D(double teta){
    windowViewport->rotacionarNaOrigem2D(ui->listaObjetos->currentItem()->text().toStdString(),teta);
    desenharFiguras();
}

void MainWindow::rotacionarNoCentro2D(double teta){
    windowViewport->rotacionarNoCentro2D(ui->listaObjetos->currentItem()->text().toStdString(),teta);
    desenharFiguras();
}

void MainWindow::rotacionarNoPonto2D(double teta, double pX, double pY){
    windowViewport->rotacionarNoPonto2D(ui->listaObjetos->currentItem()->text().toStdString(),teta,pX,pY);
    desenharFiguras();
}

void MainWindow::mudarCor(QColor cor) {
    windowViewport->mudarCor(ui->listaObjetos->currentItem()->text().toStdString(), cor.red(), cor.green(), cor.blue());
    desenharFiguras();
}
