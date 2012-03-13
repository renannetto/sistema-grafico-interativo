#include "Transformacoes.h"
#include "ui_Transformacoes.h"

Transformacoes::Transformacoes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transformacoes)
{
    ui->setupUi(this);
}

Transformacoes::~Transformacoes()
{
    delete ui;
}
