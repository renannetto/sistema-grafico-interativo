#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
}

Dialog::~Dialog()
{
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
    }
}

void Dialog::desenharReta()
{
    list<Ponto*> pontos;
    pontos.push_back(new Ponto(ui->lineEdit_3->text().toDouble(), ui->lineEdit_4->text().toDouble()));
    pontos.push_back(new Ponto(ui->lineEdit_5->text().toDouble(), ui->lineEdit_6->text().toDouble()));
    emit desenharFigura(RETA, pontos, scene->backgroundBrush().color());
}

void Dialog::desenharPonto()
{
    list<Ponto*> ponto;
    ponto.push_back(new Ponto(ui->lineEdit->text().toDouble(), ui->lineEdit_2->text().toDouble()));
    emit desenharFigura(PONTO, ponto, scene->backgroundBrush().color());
}

void Dialog::adicionarPonto()
{
    QString ponto = "(";
    ponto += ui->lineEdit_7->text();
    ponto += ", ";
    ponto += ui->lineEdit_8->text();
    ponto += ")";
    ui->listWidget->addItem(ponto);
    pontos.push_back(new Ponto(ui->lineEdit_7->text().toDouble(), ui->lineEdit_8->text().toDouble()));
}

void Dialog::desenharPoligono()
{
    if(pontos.size()>=3){
        emit desenharFigura(POLIGONO, pontos, scene->backgroundBrush().color());
        pontos.clear();
        ui->listWidget->clear();
    }
}

void Dialog::escolherCor()
{
    QColor cor = QColorDialog::getColor(Qt::black, this);
    scene->setBackgroundBrush(QBrush(cor));
}
