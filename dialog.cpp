#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::drawLine()
{
    list<Ponto*> line;
    line.push_back(new Ponto(ui->lineEdit_3->text().toDouble(), ui->lineEdit_4->text().toDouble()));
    line.push_back(new Ponto(ui->lineEdit_5->text().toDouble(), ui->lineEdit_6->text().toDouble()));
    emit drawLineM(line);
}

void Dialog::drawDot()
{
    list<Ponto*> dot;
    dot.push_back(new Ponto(ui->lineEdit->text().toDouble(), ui->lineEdit_2->text().toDouble()));
    emit drawDotM(dot);
}

void Dialog::addPoint()
{
    QString ponto = "(";
    ponto += ui->lineEdit_7->text();
    ponto += ", ";
    ponto += ui->lineEdit_8->text();
    ponto += ")";
    ui->listWidget->addItem(ponto);
    pontos.push_back(new Ponto(ui->lineEdit_7->text().toDouble(), ui->lineEdit_8->text().toDouble()));
}

void Dialog::drawPolygon()
{
    emit drawPolygonM(pontos);
    pontos.clear();
    ui->listWidget->clear();
}
