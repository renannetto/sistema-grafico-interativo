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
    emit drawLineM(ui->lineEdit_3->text().toDouble(),
ui->lineEdit_4->text().toDouble(), ui->lineEdit_5->text().toDouble(),
ui->lineEdit_6->text().toDouble());
}

void Dialog::drawDot()
{
    emit drawDotM(ui->lineEdit->text().toDouble(), ui->lineEdit_2->text().toDouble());
}
