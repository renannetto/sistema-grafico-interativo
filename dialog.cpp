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

void Dialog::receberPonto(double x, double y, double z){
    stringstream ssX;
    stringstream ssY;
    stringstream ssZ;
    ssX << x;
    ssY << y;
    ssZ << z;

    switch(this->ui->tabWidget->currentIndex()) {

    case 0 :
        this->ui->pontoX->setText(ssX.str().c_str());
        this->ui->pontoY->setText(ssY.str().c_str());
        this->ui->pontoZ->setText(ssZ.str().c_str());
        break;
    case 1 :
        this->ui->retaX1->setText(this->ui->retaX2->text());
        this->ui->retaX2->setText(ssX.str().c_str());
        this->ui->retaY1->setText(this->ui->retaY2->text());
        this->ui->retaY2->setText(ssY.str().c_str());
        this->ui->retaZ1->setText(this->ui->retaZ2->text());
        this->ui->retaZ2->setText(ssZ.str().c_str());
        break;
    case 2 :
        this->ui->lineEdit_7->setText(ssX.str().c_str());
        this->ui->lineEdit_8->setText(ssY.str().c_str());
        this->ui->lineEdit_9->setText(ssZ.str().c_str());
        this->ui->pushButton->click();
        break;
    case 3 :
        this->ui->curvaX->setText(ssX.str().c_str());
        this->ui->curvaY->setText(ssY.str().c_str());
        this->ui->curvaZ->setText(ssZ.str().c_str());
        this->ui->pushButton_6->click();
        break;
    case 4:
        this->ui->poliedroX->setText(ssX.str().c_str());
        this->ui->poliedroY->setText(ssY.str().c_str());
        this->ui->poliedroZ->setText(ssZ.str().c_str());
        this->ui->poliedroBotaoPonto->click();
        break;
    }
}

void Dialog::construirReta(){
    list<Ponto*> pontos;
    list<Face*> faces;
    pontos.push_back(new Ponto(ui->retaX1->text().toDouble(), ui->retaY1->text().toDouble(), ui->retaZ1->text().toDouble()));
    pontos.push_back(new Ponto(ui->retaX2->text().toDouble(), ui->retaY2->text().toDouble(), ui->retaZ2->text().toDouble()));
    emit construirFigura(RETA, pontos, faces, scene->backgroundBrush().color());
}

void Dialog::construirPonto(){
    list<Ponto*> ponto;
    list<Face*> faces;
    ponto.push_back(new Ponto(ui->pontoX->text().toDouble(), ui->pontoY->text().toDouble(), ui->pontoZ->text().toDouble()));
    emit construirFigura(PONTO, ponto, faces, scene->backgroundBrush().color());
}

void Dialog::adicionarPontoPoligono(){
    QString ponto = "(";
    ponto += ui->lineEdit_7->text();
    ponto += ", ";
    ponto += ui->lineEdit_8->text();
    ponto += ", ";
    ponto += ui->lineEdit_9->text();
    ponto += ")";
    ui->listWidget->addItem(ponto);
    pontosPoligono.push_back(new Ponto(ui->lineEdit_7->text().toDouble(), ui->lineEdit_8->text().toDouble(), ui->lineEdit_9->text().toDouble()));
}

void Dialog::construirPoligono(){
    list<Face*> faces;
    if(pontosPoligono.size()>=3){
        if(this->ui->checkBox->checkState() == Qt::Checked){
            emit construirFigura(POLIGONOPREENCHIDO, pontosPoligono, faces, scene->backgroundBrush().color());
        }
        else{
            emit construirFigura(POLIGONO, pontosPoligono, faces, scene->backgroundBrush().color());
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
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(ui->curvaX->text()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(ui->curvaY->text()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(ui->curvaZ->text()));
}

void Dialog::construirCurva(){
    list<Face*> faces;
    if(ui->tableWidget->rowCount()>=4){
        for(int i = 0; i < ui->tableWidget->rowCount(); i++){
	    pontosCurva.push_back(new Ponto(ui->tableWidget->item(i,0)->text().toDouble(), ui->tableWidget->item(i,1)->text().toDouble(), ui->tableWidget->item(i,2)->text().toDouble()));
        }
        if(ui->radioBezier->isChecked())
            emit construirFigura(CURVABEZIER, pontosCurva, faces, scene->backgroundBrush().color());
        if(ui->radioSpline->isChecked())
            emit construirFigura(CURVASPLINE, pontosCurva, faces, scene->backgroundBrush().color());

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
    string faces;
    double p1,p2,p3;

    if(ui->pontosPoliedro->rowCount()>=3 && ui->facesPoliedro->count()>=1){
	for(int i = 0; i < ui->pontosPoliedro->rowCount(); i++){
	    pontosPoliedro.push_back(new Ponto(ui->pontosPoliedro->item(i,0)->text().toDouble(), ui->pontosPoliedro->item(i,1)->text().toDouble(), ui->pontosPoliedro->item(i,2)->text().toDouble()));
	}
	for(int i = 0; i < ui->facesPoliedro->count(); i++){
        faces = ui->facesPoliedro->item(i)->text().toStdString();
        stringstream ss(faces);
        ss.ignore();
        ss >> p1;
        ss.ignore();
        ss >> p2;
        ss.ignore();
        ss >> p3;
        ss.ignore();
        facesPoliedro.push_back(new Face(++p1,++p2,++p3));
	}
    emit construirFigura(POLIEDRO, pontosPoliedro, facesPoliedro, scene->backgroundBrush().color());

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
