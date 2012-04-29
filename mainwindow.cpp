#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>

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
    ui->listaObjetos->addItem("Poliedro 0");

    deslocamentoClipador = 10;
    clipador = new Clipping(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                            windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);

    geradorDeCurvas = new GeradorDeCurvas();

    detectorDeEventos = this->ui->graphicsView;
    detectorDeEventos->fixarJanelaPrincipal(this);
    ui->graphicsView->setScene(viewport);
    ui->zoomText->clear();

    connect(janelaDeCriacoes, SIGNAL(construirFigura(Tipo, list<Ponto*>, list<Face*>, QColor)),
    this, SLOT(construirFigura(Tipo, list<Ponto*>, list<Face*>, QColor)));
    connect(janelaDeTransformacoes, SIGNAL(sTransladar(double,double, double)),
    this, SLOT(transladar(double,double,double)));
    connect(janelaDeTransformacoes, SIGNAL(sEscalonar(double,double, double)),
    this, SLOT(escalonar(double,double,double)));
    connect(janelaDeTransformacoes, SIGNAL(sRotacionarNaOrigem(double, double, double, double)),
    this, SLOT(rotacionarNaOrigem(double, double, double, double)));
    connect(janelaDeTransformacoes, SIGNAL(sRotacionarNoCentro(double, double, double, double)),
    this, SLOT(rotacionarNoCentro(double, double, double, double)));
    connect(janelaDeTransformacoes, SIGNAL(sRotacionarNoPonto(double,double,double, double, double, double, double)),
    this, SLOT(rotacionarNoPonto(double,double,double, double, double, double, double)));
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
    clipador->fixarCoordenadas(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                               windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
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

void MainWindow::construirFigura(Tipo tipo, list<Ponto *> pontos, list<Face*> faces, QColor cor){
    QString nome = QString::fromStdString(windowViewport->adicionarFigura(tipo, pontos, faces, cor.red(), cor.green(), cor.blue()));
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
    for (unsigned int i = 1; i < figuras.size(); i++){
        Figura* figura = figuras.back();
        pontos = figura->obterPontosPPC();

        Cor cor = figura->obterCor();
        Tipo tipoDaFigura = figura->obterTipo();

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

        if(tipoDaFigura == PONTO){
            if(!ui->checkBox->isChecked() || clipador->clippingDePonto(*pontos.front())){
                double x = transformadaViewportX(pontos.front()->obterX());
                double y = transformadaViewportY(pontos.front()->obterY());
                viewport->addLine(x,y,x,y, QPen(qCor));
            }

        } else if(tipoDaFigura == RETA){
            Ponto np1(0, 0);
            Ponto np2(0, 0);
            if (!ui->checkBox->isChecked() || clippingDeLinha(*pontos.front(), *pontos.back(), np1, np2)) {
                if(!ui->checkBox->isChecked()){
                    np1 = *pontos.front();
                    np2 = *pontos.back();
                }
                double x1 = transformadaViewportX(np1.obterX());
                double y1 = transformadaViewportY(np1.obterY());
                double x2 = transformadaViewportX(np2.obterX());
                double y2 = transformadaViewportY(np2.obterY());
                viewport->addLine(x1, y1, x2, y2, QPen(qCor));
            }

        } else if (tipoDaFigura == CURVABEZIER || tipoDaFigura == CURVASPLINE){
            list<Ponto*> pontosCurva;

            if(tipoDaFigura == CURVABEZIER)
                geradorDeCurvas->gerarBezier(pontos, pontosCurva);
            if(tipoDaFigura == CURVASPLINE)
                geradorDeCurvas->gerarBSpline(pontos, pontosCurva);

            list<Ponto*> pontosClipping;

            if(ui->checkBox->isChecked())
                clipador->clippingDeCurvas(pontosCurva, pontosClipping);
            else {
                pontosClipping = pontosCurva;
            }

            list<Ponto*>::iterator it = pontosClipping.begin();
            double x1 = (*it)->obterX();
            double y1 = (*it)->obterY();
            double x2;
            double y2;
            for (++it; it!=pontosClipping.end(); it++) {
                if(*it != 0){
                    x2 = (*it)->obterX();
                    y2 = (*it)->obterY();
                    viewport->addLine(transformadaViewportX(x1), transformadaViewportY(y1), transformadaViewportX(x2), transformadaViewportY(y2), QPen(qCor));
                    x1 = x2;
                    y1 = y2;
                } else{
                    it++;
                    x1 = (*it)->obterX();
                    y1 = (*it)->obterY();
                }
            }

            pontosCurva.clear();
            pontosClipping.clear();

	} else if(tipoDaFigura == POLIEDRO){
	    list<Face*> faces = figura->obterFaces();
	    int *pontosFace;
	    Ponto **pontosFigura = new Ponto*[pontos.size()];
	    list<Ponto*> pontosParaClippar;
	    list<Ponto*> nPontos;

	    QPolygonF poligono;

	    Ponto* ponto;
	    for (unsigned int i=0; i<pontos.size(); i++) {
		ponto = pontos.front();
		pontosFigura[i] = ponto;
		pontos.pop_front();
		pontos.push_back(ponto);
	    }

	    list<Face*>::iterator it;
	    int ponto1;
	    int ponto2;
	    int ponto3;
        for (it=faces.begin(); it!=faces.end(); it++) {
            pontosFace = (*it)->obterPontos();
            ponto1 = pontosFace[0];
            ponto2 = pontosFace[1];
            ponto3 = pontosFace[2];
            pontosParaClippar.push_back(pontosFigura[ponto1-1]);
            pontosParaClippar.push_back(pontosFigura[ponto2-1]);
            pontosParaClippar.push_back(pontosFigura[ponto3-1]);

            if(!ui->checkBox->isChecked() || clipador->clippingDePoligonosSutherland(pontosParaClippar, nPontos)){
                if(!ui->checkBox->isChecked())
                    nPontos = pontosParaClippar;
                int size = nPontos.size();
                for (int i=0; i<size; i++) {
                    Ponto* ponto = nPontos.front();
                    poligono << QPointF(transformadaViewportX(ponto->obterX()), transformadaViewportY(ponto->obterY()));

                    nPontos.pop_front();
                }
                //		double p1x = transformadaViewportX(pontosFigura[ponto1-1]->obterX());
                //		double p1y = transformadaViewportY(pontosFigura[ponto1-1]->obterY());
                //		double p2x = transformadaViewportX(pontosFigura[ponto2-1]->obterX());
                //		double p2y = transformadaViewportY(pontosFigura[ponto2-1]->obterY());
                //		double p3x = transformadaViewportX(pontosFigura[ponto3-1]->obterX());
                //		double p3y = transformadaViewportY(pontosFigura[ponto3-1]->obterY());
                //		poligono << QPointF(p1x, p1y);
                //		poligono << QPointF(p2x, p2y);
                //		poligono << QPointF(p3x, p3y);
                viewport->addPolygon(poligono, QPen(qCor));
                poligono.clear();
            }
            nPontos.clear();
            pontosParaClippar.clear();
        }
	} else{
	    QPolygonF poligono;
	    list<Ponto*> nPontos;

	    if(!ui->checkBox->isChecked() || clipador->clippingDePoligonosSutherland(pontos, nPontos)){
		if(!ui->checkBox->isChecked())
		    nPontos = pontos;
		int size = nPontos.size();
		for (int i=0; i<size; i++) {
		    Ponto* ponto = nPontos.front();

		    poligono << QPointF(transformadaViewportX(ponto->obterX()), transformadaViewportY(ponto->obterY()));

		    nPontos.pop_front();
		    nPontos.push_back(ponto);
		}
		if(figura->obterTipo() == POLIGONOPREENCHIDO){
		    int rPreenchimento = cor.obterVermelho() / 2;
		    int gPreenchimento = cor.obterVerde() / 2;
		    int bPreenchimento = cor.obterAzul() / 2;

		    viewport->addPolygon(poligono, QPen(QColor::fromRgb(rPreenchimento,gPreenchimento,bPreenchimento)), QBrush(qCor));
		}
		else{
		    viewport->addPolygon(poligono, QPen(qCor));
		}
		nPontos.clear();
	    }
	}
	figuras.pop_back();
	figuras.push_front(figura);
    }
}

bool MainWindow::clippingDeLinha(Ponto const &p1, Ponto const &p2, Ponto &np1, Ponto &np2){
    return clipador->clippingDeLinha(p1, p2, np1, np2);
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
    Ponto ponto(xn,yn,0);
    windowViewport->transformarPontoWindowParaMundo(ponto);

    if(janelaDeCriacoes->isVisible()){
        janelaDeCriacoes->receberPonto(ponto.obterX(),ponto.obterY(),ponto.obterZ());
    }
    if(janelaDeTransformacoes->isVisible()){
        janelaDeTransformacoes->receberPonto(ponto.obterX(),ponto.obterY(),ponto.obterZ());
    }    
    deslocamentoXDaCamera = ponto.obterX();
    deslocamentoYDaCamera = ponto.obterY();
    deslocamentoZDaCamera = ponto.obterZ();
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

void MainWindow::moverParaFrente(){
windowViewport->moverParaFrente();
windowViewport->gerarDescricoesPPC();
clipador->fixarCoordenadas(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                           windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
desenharFiguras();
}

void MainWindow::moverParaTras(){
    windowViewport->moverParaTras();
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

void MainWindow::transladar(double vX, double vY, double vZ){
    windowViewport->transladar(ui->listaObjetos->currentItem()->text().toStdString(),vX,vY,vZ);
    windowViewport->gerarDescricoesPPC();
    desenharFiguras();
}

void MainWindow::escalonar(double vX, double vY, double vZ){
    windowViewport->escalonar(ui->listaObjetos->currentItem()->text().toStdString(),vX,vY,vZ);
    windowViewport->gerarDescricoesPPC();
    desenharFiguras();
}

void MainWindow::rotacionarNaOrigem(double teta, double ux, double uy, double uz){
    Ponto vetor(ux, uy, uz);
    vetor.normalizarVetor();
    windowViewport->rotacionarNaOrigem(ui->listaObjetos->currentItem()->text().toStdString(), teta, vetor);
    windowViewport->gerarDescricoesPPC();
    desenharFiguras();
}

void MainWindow::rotacionarNoCentro(double teta, double ux, double uy, double uz){
    Ponto vetor(ux, uy, uz);
    vetor.normalizarVetor();
    windowViewport->rotacionarNoCentro(ui->listaObjetos->currentItem()->text().toStdString(), teta, vetor);
    windowViewport->gerarDescricoesPPC();
    desenharFiguras();
}

void MainWindow::rotacionarNoPonto(double teta, double pX, double pY, double pZ, double ux, double uy, double uz){
    Ponto vetor(ux, uy, uz);
    vetor.normalizarVetor();
    windowViewport->rotacionarNoPonto(ui->listaObjetos->currentItem()->text().toStdString(),teta, pX, pY, pZ, vetor);
    windowViewport->gerarDescricoesPPC();
    desenharFiguras();
}

void MainWindow::mudarCor(QColor cor) {
    windowViewport->mudarCor(ui->listaObjetos->currentItem()->text().toStdString(), cor.red(), cor.green(), cor.blue());
    desenharFiguras();
}
void MainWindow::rotacionarWindowParaDireita() {

    Ponto vetor(ui->rotacaoWindowX->text().toDouble(), ui->rotacaoWindowY->text().toDouble(), ui->rotacaoWindowZ->text().toDouble());
    vetor.normalizarVetor();

    windowViewport->rotacionarWindow(vetor, ui->editGraus->text().toDouble());
    windowViewport->gerarDescricoesPPC();
    clipador->fixarCoordenadas(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                               windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
    desenharFiguras();
}

void MainWindow::rotacionarWindowParaEsquerda() {

    Ponto vetor(ui->rotacaoWindowX->text().toDouble(), ui->rotacaoWindowY->text().toDouble(), ui->rotacaoWindowZ->text().toDouble());
    vetor.normalizarVetor();

    windowViewport->rotacionarWindow(vetor, (double)360 - ui->editGraus->text().toDouble());
    windowViewport->gerarDescricoesPPC();
    clipador->fixarCoordenadas(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                               windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
    desenharFiguras();
}

void MainWindow::aumentarRegiaoDeClipping(){
    if(this->ui->checkBox->isChecked()){
        if(deslocamentoClipador > 5)
            deslocamentoClipador -= 3;
        clipador->fixarCoordenadas(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                                   windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
        desenharFiguras();
    }
}

void MainWindow::diminuirRegiaoDeClipping(){
    if(this->ui->checkBox->isChecked()){
        if(deslocamentoClipador < 45)
            deslocamentoClipador += 3;
        clipador->fixarCoordenadas(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
                                   windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
        desenharFiguras();
    }
}

void MainWindow::fixarAlgoritmoDeClipping() {
    if (ui->radioCohen->isChecked())
        clipador->fixarAlgoritmoDeClipping(1);
    else
        clipador->fixarAlgoritmoDeClipping(0);
}

void MainWindow::arrastarCamera(double x, double y){
    if(!janelaDeCriacoes->isVisible() && !janelaDeTransformacoes->isVisible()){
	double xn = transformadaInversaViewportX(x);
	double yn = transformadaInversaViewportY(y);
    Ponto ponto(xn,yn,0);
    windowViewport->transformarPontoWindowParaMundo(ponto);

    windowViewport->transladar("Window", deslocamentoXDaCamera - ponto.obterX(), deslocamentoYDaCamera - ponto.obterY(), deslocamentoZDaCamera - ponto.obterZ());
	windowViewport->gerarDescricoesPPC();
	clipador->fixarCoordenadas(windowViewport->obterXMinDaWindowPPC(), windowViewport->obterXMaxDaWindowPPC(),
				   windowViewport->obterYMinDaWindowPPC(), windowViewport->obterYMaxDaWindowPPC(), deslocamentoClipador);
	desenharFiguras();
    }
}

void MainWindow::fixarForward(){
    if (ui->check_forward->isChecked())
        geradorDeCurvas->fixarForward(true);
    else
        geradorDeCurvas->fixarForward(false);
}
