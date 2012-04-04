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

    janelaDeCriacoes = new Dialog(this);
    janelaDeCriacoes->setVisible(false);
    janelaDeTransformacoes = new Transformacoes(this);
    janelaDeTransformacoes->setVisible(false);
    clipador = new Clipping(SUBVIEWPORTXMIN, SUBVIEWPORTXMAX, SUBVIEWPORTYMIN, SUBVIEWPORTYMAX);
    viewport = new QGraphicsScene(0,0,VIEWPORTXSIZE,VIEWPORTYSIZE);
    windowViewport = new WindowViewport();
    detectorDeEventos = this->ui->graphicsView;
    detectorDeEventos->fixarJanelaPrincipal(this);
    ui->graphicsView->setScene(viewport);
    ui->zoomText->clear();

    connect(janelaDeCriacoes, SIGNAL(desenharFigura(Tipo, list<Ponto*>, QColor)),
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

    mostrarValorDoZoom(ui->zoomSlider->value());
    desenharFiguras();
}

void MainWindow::reiniciar(){
    delete janelaDeCriacoes;
    delete windowViewport;
    delete viewport;

    iniciar();
}

void MainWindow::resetarWindow(){
    windowViewport->resetarWindow();
    desenharFiguras();
}

void MainWindow::abrirJanelaDeCriacoes(){
    janelaDeCriacoes->setVisible(true);
}

void MainWindow::abrirJanelaDeTransformacoes(){
    if(this->ui->listaObjetos->currentItem()->text() == "Novo Objeto")
        janelaDeCriacoes->setVisible(true);
    else
        janelaDeTransformacoes->setVisible(true);
}

void MainWindow::abrirJanelaDeAjuda(){
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
    desenharSubViewport();
    list<Figura*> figuras = windowViewport->obterFiguras();
    list<Ponto*> pontos;
    for (int i = 1; i < figuras.size(); i++){
        Figura* figura = figuras.back();
        pontos = figura->obterPontosPPC();

        Cor cor = figura->obterCor();

        QColor qCor = QColor::fromRgb(cor.obterVermelho(), cor.obterVerde(), cor.obterAzul());

//        double xP,yP,xa,ya,x,y;
//        xP = xa = transformadaViewportX(pontos.front()->obterX());
//        yP = ya = transformadaViewportY(pontos.front()->obterY());
//
//        list<Ponto*>::iterator it;
//        for(it = pontos.begin(); it != pontos.end(); it++){
//            x = transformadaViewportX((*it)->obterX());
//            y = transformadaViewportY((*it)->obterY());
//            viewport->addLine(xa,ya,x,y, QPen(qCor));
//            xa = x;
//            ya = y;
//        }
//        viewport->addLine(x,y,xP,yP, QPen(qCor));
        if(pontos.size()==1){
            double x = transformadaViewportX(pontos.front()->obterX());
            double y = transformadaViewportY(pontos.front()->obterY());
            Ponto ponto(x,y);
            if(clipador->clippingDePonto(ponto)){
                viewport->addLine(x,y,x,y, QPen(qCor));
            }
        } else if(pontos.size()==2){
            double x1 = transformadaViewportX(pontos.front()->obterX());
            double y1 = transformadaViewportY(pontos.front()->obterY());
            double x2 = transformadaViewportX(pontos.back()->obterX());
            double y2 = transformadaViewportY(pontos.back()->obterY());
            Ponto ponto1(x1,y1);
            Ponto ponto2(x2, y2);
            Ponto np1(ponto1);
            Ponto np2(ponto2);
                if(clipador->clippingDeLinhaCohen(ponto1,ponto2,np1,np2)){
                    viewport->addLine(np1.obterX(),np1.obterY(),np2.obterX(),np2.obterY());
                }
        } else{
            QPolygonF poligono;
            int size = pontos.size();
            for (int i=0; i<size; i++) {
                Ponto* ponto = pontos.front();
                poligono << QPointF(transformadaViewportX(ponto->obterX()), transformadaViewportY(ponto->obterY()));

                pontos.pop_front();
                pontos.push_back(ponto);
            }
            viewport->addPolygon(poligono, QPen(qCor), QBrush(qCor));
        }
        figuras.pop_back();
        figuras.push_front(figura);
    }
}

void MainWindow::desenharSubViewport(){
    viewport->addLine(SUBVIEWPORTXMIN,SUBVIEWPORTYMIN,SUBVIEWPORTXMAX,SUBVIEWPORTYMIN);
    viewport->addLine(SUBVIEWPORTXMAX,SUBVIEWPORTYMIN,SUBVIEWPORTXMAX,SUBVIEWPORTYMAX);
    viewport->addLine(SUBVIEWPORTXMAX,SUBVIEWPORTYMAX,SUBVIEWPORTXMIN,SUBVIEWPORTYMAX);
    viewport->addLine(SUBVIEWPORTXMIN,SUBVIEWPORTYMAX,SUBVIEWPORTXMIN,SUBVIEWPORTYMIN);
}

double MainWindow::transformadaViewportX(double x){
    double xMin = windowViewport->obterXMinDaWindowPPC();
    double xMax = windowViewport->obterXMaxDaWindowPPC();
    return (x - xMin) * VIEWPORTXSIZE / (xMax - xMin);
}

double MainWindow::transformadaViewportY(double y){
    double yMin = windowViewport->obterYMinDaWindowPPC();
    double yMax = windowViewport->obterYMaxDaWindowPPC();
    return (yMax - y) * VIEWPORTYSIZE / (yMax - yMin);
}

double MainWindow::transformadaInversaViewportX(double x){
    double xMin = windowViewport->obterXMinDaWindowPPC();
    double xMax = windowViewport->obterXMaxDaWindowPPC();
    return x * (xMax - xMin) / VIEWPORTXSIZE + xMin;
}

double MainWindow::transformadaInversaViewportY(double y){
    double yMin = windowViewport->obterYMinDaWindowPPC();
    double yMax = windowViewport->obterYMaxDaWindowPPC();
    return yMax - (y * (yMax - yMin) / VIEWPORTYSIZE);
}

void MainWindow::receberPonto(double x, double y){
    double xn = transformadaInversaViewportX(x);
    double yn = transformadaInversaViewportY(y);
    double teta = (360-windowViewport->obterAnguloDaWindow())*M_PI/180;
    double centroXDaWindowPPC = windowViewport->obterCentroXDaWindow();
    double centroYDaWindowPPC = windowViewport->obterCentroYDaWindow();

    x = xn*cos(teta)-yn*sin(teta) + centroXDaWindowPPC;
    y = yn*cos(teta)+xn*sin(teta) + centroYDaWindowPPC;

    if(janelaDeCriacoes->isVisible()){
        janelaDeCriacoes->receberPontoX(x);
        janelaDeCriacoes->receberPontoY(y);
    }
    if(janelaDeTransformacoes->isVisible()){
        janelaDeTransformacoes->receberPontoX(x);
        janelaDeCriacoes->receberPontoY(y);
    }
}

void MainWindow::zoomIn(){
    windowViewport->zoomIn(ui->zoomSlider->sliderPosition());
    windowViewport->gerarDescricoesPPC();
    desenharFiguras();
}

void MainWindow::zoomOut(){
    windowViewport->zoomOut(ui->zoomSlider->sliderPosition());
    windowViewport->gerarDescricoesPPC();
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
    windowViewport->gerarDescricoesPPC();
    desenharFiguras();
}

void MainWindow::moverParaDireita(){
    windowViewport->moverParaDireita();
    windowViewport->gerarDescricoesPPC();
    desenharFiguras();
}

void MainWindow::moverParaBaixo(){
    windowViewport->moverParaBaixo();
    windowViewport->gerarDescricoesPPC();
    desenharFiguras();
}

void MainWindow::moverParaCima(){
    windowViewport->moverParaCima();
    windowViewport->gerarDescricoesPPC();
    desenharFiguras();
}

void MainWindow::transladar2D(double vX, double vY){
    windowViewport->transladar2D(ui->listaObjetos->currentItem()->text().toStdString(),vX,vY);
    windowViewport->gerarDescricoesPPC();
    desenharFiguras();
}

void MainWindow::escalonar2D(double vX, double vY){
    windowViewport->escalonar2D(ui->listaObjetos->currentItem()->text().toStdString(),vX,vY);
    windowViewport->gerarDescricoesPPC();
    desenharFiguras();
}

void MainWindow::rotacionarNaOrigem2D(double teta){
    windowViewport->rotacionarNaOrigem2D(ui->listaObjetos->currentItem()->text().toStdString(),teta);
    windowViewport->gerarDescricoesPPC();
    desenharFiguras();
}

void MainWindow::rotacionarNoCentro2D(double teta){
    windowViewport->rotacionarNoCentro2D(ui->listaObjetos->currentItem()->text().toStdString(),teta);
    windowViewport->gerarDescricoesPPC();
    desenharFiguras();
}

void MainWindow::rotacionarNoPonto2D(double teta, double pX, double pY){
    windowViewport->rotacionarNoPonto2D(ui->listaObjetos->currentItem()->text().toStdString(),teta,pX,pY);
    windowViewport->gerarDescricoesPPC();
    desenharFiguras();
}

void MainWindow::mudarCor(QColor cor) {
    windowViewport->mudarCor(ui->listaObjetos->currentItem()->text().toStdString(), cor.red(), cor.green(), cor.blue());
    desenharFiguras();
}
void MainWindow::rotacionarWindowParaDireita() {

    windowViewport->rotacionarNoCentro2D("Window", ui->editGraus->text().toDouble());
    windowViewport->gerarDescricoesPPC();
    desenharFiguras();
}

void MainWindow::rotacionarWindowParaEsquerda() {
    windowViewport->rotacionarNoCentro2D("Window", (double)360 - ui->editGraus->text().toDouble());
    windowViewport->gerarDescricoesPPC();
    desenharFiguras();
}
