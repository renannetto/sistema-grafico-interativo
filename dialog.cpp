#include "dialog.h"
#include "ui_dialog.h"
#include <iostream>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
}

Dialog::~Dialog(){
    delete ui;

}

void Dialog::receberPontoX(double x){
    stringstream ssX;
    ssX << x;

    switch(this->ui->tabWidget->currentIndex()) {

    case 0 :
        this->ui->lineEdit->setText(ssX.str().c_str());

        break;
    case 1 :
        this->ui->lineEdit_3->setText(this->ui->lineEdit_5->text());
        this->ui->lineEdit_5->setText(ssX.str().c_str());

        break;
    case 2 :
        this->ui->lineEdit_7->setText(ssX.str().c_str());

        break;
    case 3 :
        this->ui->lineEdit_9->setText(ssX.str().c_str());
        break;
    }
}

void Dialog::receberPontoY(double y){
    stringstream ssY;
    ssY << y;

    switch(this->ui->tabWidget->currentIndex()) {

    case 0 :
        this->ui->lineEdit_2->setText(ssY.str().c_str());

        break;
    case 1 :
        this->ui->lineEdit_4->setText(this->ui->lineEdit_6->text());
        this->ui->lineEdit_6->setText(ssY.str().c_str());

        break;
    case 2 :
        this->ui->lineEdit_8->setText(ssY.str().c_str());
        this->ui->pushButton->click();

        break;
    case 3 :
        this->ui->lineEdit_10->setText(ssY.str().c_str());
        this->ui->pushButton_6->click();
        break;
    }
}

void Dialog::construirReta(){
    list<Ponto*> pontos;
    pontos.push_back(new Ponto(ui->lineEdit_3->text().toDouble(), ui->lineEdit_4->text().toDouble()));
    pontos.push_back(new Ponto(ui->lineEdit_5->text().toDouble(), ui->lineEdit_6->text().toDouble()));
    emit construirFigura(RETA, pontos, scene->backgroundBrush().color());
}

void Dialog::construirPonto(){
    list<Ponto*> ponto;
    ponto.push_back(new Ponto(ui->lineEdit->text().toDouble(), ui->lineEdit_2->text().toDouble()));
    emit construirFigura(PONTO, ponto, scene->backgroundBrush().color());
}

void Dialog::adicionarPontoPoligono(){
    QString ponto = "(";
    ponto += ui->lineEdit_7->text();
    ponto += ", ";
    ponto += ui->lineEdit_8->text();
    ponto += ")";
    ui->listWidget->addItem(ponto);
    pontosPoligono.push_back(new Ponto(ui->lineEdit_7->text().toDouble(), ui->lineEdit_8->text().toDouble()));
}

void Dialog::construirPoligono(){
    if(pontosPoligono.size()>=3){
        if(this->ui->checkBox->checkState() == Qt::Checked){
            emit construirFigura(POLIGONOPREENCHIDO, pontosPoligono, scene->backgroundBrush().color());
        }
        else{
            emit construirFigura(POLIGONO, pontosPoligono, scene->backgroundBrush().color());
        }
        pontosPoligono.clear();

        ui->listWidget->clear();
    }
}

void Dialog::adicionarPontoCurva(){
    stringstream string;
    string << ui->tableWidget->rowCount();
    QString s = "Ponto " + QString::fromStdString(string.str());
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setVerticalHeaderItem(ui->tableWidget->rowCount()-1, new QTableWidgetItem(s));;
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(ui->lineEdit_9->text()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(ui->lineEdit_10->text()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem("0"));
}

void Dialog::construirCurva(){
    if(ui->tableWidget->rowCount()>=4){
        for(int i = 0; i < ui->tableWidget->rowCount(); i++){
	    pontosCurva.push_back(new Ponto(ui->tableWidget->item(i,0)->text().toDouble(), ui->tableWidget->item(i,1)->text().toDouble(), ui->tableWidget->item(i,2)->text().toDouble()));
        }
        if(ui->radioBezier->isChecked())
            emit construirFigura(CURVABEZIER, pontosCurva, scene->backgroundBrush().color());
        if(ui->radioSpline->isChecked())
            emit construirFigura(CURVASPLINE, pontosCurva, scene->backgroundBrush().color());

        pontosCurva.clear();
        //ui->tableWidget->clear();
        while(ui->tableWidget->rowCount())
            ui->tableWidget->removeRow(0);
    }
}

void Dialog::adicionarPontoPoliedro(){
    stringstream string;
    string << ui->pontosPoliedro->rowCount();
    QString s = "Ponto " + QString::fromStdString(string.str());
    ui->pontosPoliedro->insertRow(ui->pontosPoliedro->rowCount());
    ui->pontosPoliedro->setVerticalHeaderItem(ui->pontosPoliedro->rowCount()-1, new QTableWidgetItem(s));;
    ui->pontosPoliedro->setItem(ui->pontosPoliedro->rowCount()-1, 0, new QTableWidgetItem(ui->poliedroX->text()));
    ui->pontosPoliedro->setItem(ui->pontosPoliedro->rowCount()-1, 1, new QTableWidgetItem(ui->poliedroY->text()));
    ui->pontosPoliedro->setItem(ui->pontosPoliedro->rowCount()-1, 2, new QTableWidgetItem(ui->poliedroZ->text()));
}

void Dialog::adicionarFacePoliedro(){
    int qtdDePontos = ui->pontosPoliedro->rowCount();
    if (ui->poliedroP1->text().toInt() < qtdDePontos && ui->poliedroP2->text().toInt() < qtdDePontos && ui->poliedroP3->text().toInt() < qtdDePontos){
	QString ponto = "(";
	ponto += ui->poliedroP1->text();
	ponto += ", ";
	ponto += ui->poliedroP2->text();
	ponto += ", ";
	ponto += ui->poliedroP3->text();
	ponto += ")";
	ui->facesPoliedro->addItem(ponto);
    }
}

void Dialog::construirPoliedro(){
    list<Ponto*> pontosPoliedro;
    list<Face*> facesPoliedro;
    if(ui->pontosPoliedro->rowCount()>=3 && ui->facesPoliedro->count()>=1){
	for(int i = 0; i < ui->pontosPoliedro->rowCount(); i++){
	    pontosPoliedro.push_back(new Ponto(ui->pontosPoliedro->item(i,0)->text().toDouble(), ui->pontosPoliedro->item(i,1)->text().toDouble(), ui->pontosPoliedro->item(i,2)->text().toDouble()));
	}
	for(int i = 0; i < ui->facesPoliedro->count(); i++){
	    //add faces
	}
	//emit construirFigura(POLIEDRO, pontosPoliedro, facesPoliedro, scene->backgroundBrush().color());

	ui->facesPoliedro->clear();
	while(ui->pontosPoliedro->rowCount())
	    ui->pontosPoliedro->removeRow(0);
    }
}

void Dialog::escolherCor(){
    QColor cor = QColorDialog::getColor(Qt::black, this);
    scene->setBackgroundBrush(QBrush(cor));
}

void Dialog::limparTudo(){
    ui->listWidget->clear();
    pontosPoligono.clear();
    while(ui->tableWidget->rowCount())
	ui->tableWidget->removeRow(0);
}
