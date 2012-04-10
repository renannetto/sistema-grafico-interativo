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
    //clipador = new Clipping(SUBVIEWPORTXMIN, SUBVIEWPORTXMAX, SUBVIEWPORTYMIN, SUBVIEWPORTYMAX);
    viewport = new QGraphicsScene(0,0,VIEWPORTXSIZE,VIEWPORTYSIZE);
    windowViewport = new WindowViewport();

    deslocamentoClipador = 10;
    clipador = new Clipping(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                            windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
    detectorDeEventos = this->ui->graphicsView;
    detectorDeEventos->fixarJanelaPrincipal(this);
    ui->graphicsView->setScene(viewport);
    ui->zoomText->clear();

    connect(janelaDeCriacoes, SIGNAL(construirFigura(Tipo, list<Ponto*>, QColor)),
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
    construirMatrizes();
    desenharFiguras();
}

void MainWindow::reiniciar(){
    delete janelaDeCriacoes;
    delete windowViewport;
    delete viewport;

    iniciar();
}

void MainWindow::construirMatrizes(){
    matrizBezier[0][0] = -1; matrizBezier[0][1] = 3; matrizBezier[0][2] = -3; matrizBezier[0][3] = 1;
    matrizBezier[1][0] = 3; matrizBezier[1][1] = -6; matrizBezier[1][2] = 3; matrizBezier[1][3] = 0;
    matrizBezier[2][0] = -3; matrizBezier[2][1] = 3; matrizBezier[2][2] = 0; matrizBezier[2][3] = 0;
    matrizBezier[3][0] = 1; matrizBezier[3][1] = 0; matrizBezier[3][2] = 0; matrizBezier[3][3] = 0;
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

        if(figura->obterTipo() == PONTO){
            if(clipador->clippingDePonto(*pontos.front())){
                double x = transformadaViewportX(pontos.front()->obterX());
                double y = transformadaViewportY(pontos.front()->obterY());
                viewport->addLine(x,y,x,y, QPen(qCor));
            }
        } else if(figura->obterTipo() == RETA){
            Ponto np1(0, 0);
            Ponto np2(0, 0);
            if (cliparReta(*pontos.front(), *pontos.back(), np1, np2)) {
                double x1 = transformadaViewportX(np1.obterX());
                double y1 = transformadaViewportY(np1.obterY());
                double x2 = transformadaViewportX(np2.obterX());
                double y2 = transformadaViewportY(np2.obterY());
                viewport->addLine(x1, y1, x2, y2, QPen(qCor));
            }
        } else if (figura->obterTipo() == CURVABEZIER){
            list<Ponto*>::iterator it = pontos.begin();
            double constantesX[4], constantesY[4];
            //int nPassos = (100.0/sqrt(clipador->obterYMax() - clipador->obterYMin()))*3.0;
            int nPassos = 40;
            double xMin = clipador->obterXMin();
            double xMax = clipador->obterXMax();
            double yMin = clipador->obterYMin();
            double yMax = clipador->obterYMax();
            for(int i = 0; i < (pontos.size()-1)/3; i++){
                Ponto* p1 = *it++;
                Ponto* p2 = *it++;
                Ponto* p3 = *it++;
                Ponto* p4 = *it;
                for(int j = 0; j < 4; j++){
                    constantesX[j] = 0;
                    constantesY[j] = 0;

                    constantesX[j] += matrizBezier[j][0]*p1->obterX();
                    constantesY[j] += matrizBezier[j][0]*p1->obterY();
                    constantesX[j] += matrizBezier[j][1]*p2->obterX();
                    constantesY[j] += matrizBezier[j][1]*p2->obterY();
                    constantesX[j] += matrizBezier[j][2]*p3->obterX();
                    constantesY[j] += matrizBezier[j][2]*p3->obterY();
                    constantesX[j] += matrizBezier[j][3]*p4->obterX();
                    constantesY[j] += matrizBezier[j][3]*p4->obterY();
                }
                double x1,x2,y1,y2;
                x1 = constantesX[3];
                y1 = constantesY[3];
                std::cout << nPassos << " | X1 = " << x1 << "X2 = " << y1 << std::endl;
                for(int j = 1; j <= nPassos; j++){
                    double passo = (double)j/(double)nPassos;
                    x2 = ((constantesX[0]*passo + constantesX[1])*passo + constantesX[2])*passo + constantesX[3];
                    y2 = ((constantesY[0]*passo + constantesY[1])*passo + constantesY[2])*passo + constantesY[3];
                    if (x1 > xMin && x1 < xMax && y1 > yMin && y1 <yMax) { //ponto 1 dentro
                        if (x2 > xMin && x2 < xMax && y2 > yMin && y2 <yMax) { //ponto 2 dentro => não precisa clipar
                            viewport->addLine(transformadaViewportX(x1),transformadaViewportY(y1),transformadaViewportX(x2),transformadaViewportY(y2),QPen(qCor));
                        } else {
                            Ponto p1(x1, y1);
                            Ponto p2(x2, y2);
                            Ponto np1(0, 0);
                            Ponto np2(0, 0);
                            if (cliparReta(p1, p2, np1, np2))
                                viewport->addLine(transformadaViewportX(np1.obterX()),transformadaViewportY(np1.obterY()),transformadaViewportX(np2.obterX()),transformadaViewportY(np2.obterY()),QPen(qCor));
                        }
                    } else { //ponto 1 fora
                        if (x2 > xMin && x2 < xMax && y2 > yMin && y2 <yMax) { //ponto 2 dentro => precisa clipar
                            Ponto p1(x1, y1);
                            Ponto p2(x2, y2);
                            Ponto np1(0, 0);
                            Ponto np2(0, 0);
                            if (cliparReta(p1, p2, np1, np2))
                                viewport->addLine(transformadaViewportX(np1.obterX()),transformadaViewportY(np1.obterY()),transformadaViewportX(np2.obterX()),transformadaViewportY(np2.obterY()),QPen(qCor));
                        }
                    }
                    x1 = x2;
                    y1 = y2;
                }
            }
        } else{
            QPolygonF poligono;
            list<Ponto*> npontos;

            if(clipador->clippingDePoligonosSutherland(pontos, npontos)){
                int size = npontos.size();
                for (int i=0; i<size; i++) {
                    Ponto* ponto = npontos.front();
                    poligono << QPointF(transformadaViewportX(ponto->obterX()), transformadaViewportY(ponto->obterY()));

                    npontos.pop_front();
                    npontos.push_back(ponto);
                }
                if(figura->obterTipo() == POLIGONOPREENCHIDO){
                    viewport->addPolygon(poligono, QPen(qCor), QBrush(qCor));
                }
                else{
                    viewport->addPolygon(poligono, QPen(qCor));
                }
            }
        }
        figuras.pop_back();
        figuras.push_front(figura);
    }
}

bool MainWindow::cliparReta(Ponto const &p1, Ponto const &p2, Ponto &np1, Ponto &np2){
    if (ui->radioCohen->isChecked())
        return clipador->clippingDeLinhaCohen(p1, p2, np1, np2);
    else
        return clipador->clippingDeLinhaLiang(p1, p2, np1, np2);
}

void MainWindow::desenharSubViewport(){
    double xMin = transformadaViewportX(clipador->obterXMin());
    double xMax = transformadaViewportX(clipador->obterXMax());
    double yMin = transformadaViewportY(clipador->obterYMin());
    double yMax = transformadaViewportY(clipador->obterYMax());
    viewport->addLine(xMin, yMin, xMax, yMin);
    viewport->addLine(xMax,yMin,xMax,yMax);
    viewport->addLine(xMax,yMax,xMin,yMax);
    viewport->addLine(xMin,yMax,xMin,yMin);
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
        janelaDeTransformacoes->receberPontoY(y);
    }
}

void MainWindow::zoomIn(){
    windowViewport->zoomIn(ui->zoomSlider->sliderPosition());
    windowViewport->gerarDescricoesPPC();
    clipador->fixarCoordenadas(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                               windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
    desenharFiguras();
}

void MainWindow::zoomOut(){
    windowViewport->zoomOut(ui->zoomSlider->sliderPosition());
    windowViewport->gerarDescricoesPPC();
    clipador->fixarCoordenadas(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                               windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
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
    clipador->fixarCoordenadas(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                               windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
    desenharFiguras();
}

void MainWindow::moverParaDireita(){
    windowViewport->moverParaDireita();
    windowViewport->gerarDescricoesPPC();
    clipador->fixarCoordenadas(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                               windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
    desenharFiguras();
}

void MainWindow::moverParaBaixo(){
    windowViewport->moverParaBaixo();
    windowViewport->gerarDescricoesPPC();
    clipador->fixarCoordenadas(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                               windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
    desenharFiguras();
}

void MainWindow::moverParaCima(){
    windowViewport->moverParaCima();
    windowViewport->gerarDescricoesPPC();
    clipador->fixarCoordenadas(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                               windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
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
    clipador->fixarCoordenadas(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                               windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
    desenharFiguras();
}

void MainWindow::rotacionarWindowParaEsquerda() {
    windowViewport->rotacionarNoCentro2D("Window", (double)360 - ui->editGraus->text().toDouble());
    windowViewport->gerarDescricoesPPC();
    clipador->fixarCoordenadas(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                               windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
    desenharFiguras();
}

void MainWindow::aumentarRegiaoDeClipping(){
    if(this->ui->checkBox->checkState() == Qt::Checked){
        if(deslocamentoClipador > 5)
            deslocamentoClipador -= 3;
        clipador->fixarCoordenadas(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                                   windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
        desenharFiguras();
    }
}

void MainWindow::diminuirRegiaoDeClipping(){
    if(this->ui->checkBox->checkState() == Qt::Checked){
        if(deslocamentoClipador < 45)
            deslocamentoClipador += 3;
        clipador->fixarCoordenadas(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                                   windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
        desenharFiguras();
    }
}
