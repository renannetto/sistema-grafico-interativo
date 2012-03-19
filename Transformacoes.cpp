#include "Transformacoes.h"
#include "ui_Transformacoes.h"

Transformacoes::Transformacoes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transformacoes)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
}

Transformacoes::~Transformacoes()
{
    delete ui;
}

void Transformacoes::receberPontoX(double x){
    stringstream ssX;
    ssX << x;

    this->ui->rotacaoPontoX->setText(ssX.str().c_str());
}

void Transformacoes::receberPontoY(double y){
    stringstream ssY;
    ssY << y;

    this->ui->rotacaoPontoY->setText(ssY.str().c_str());
}

void Transformacoes::transladar2D(){
    double vX = ui->deslocamentoXEdit->text().toDouble();
    double vY = ui->deslocamentoYEdit->text().toDouble();
    emit sTransladar2D(vX,vY);
}

void Transformacoes::escalonar2D(){
    double vX = ui->escalonamentoXEdit->text().toDouble();
    double vY = ui->escalonamentoYEdit->text().toDouble();
    emit sEscalonar2D(vX,vY);
}

void Transformacoes::rotacionarNaOrigem2D(){
    double teta = ui->anguloRotacao->text().toDouble();
    emit sRotacionarNaOrigem(teta);
}

void Transformacoes::rotacionarNoCentro2D(){
    double teta = ui->anguloRotacao->text().toDouble();
    emit sRotacionarNoCentro(teta);
}

void Transformacoes::rotacionarNoPonto2D(){
    double teta = ui->anguloRotacao->text().toDouble();
    double pX = ui->rotacaoPontoX->text().toDouble();
    double pY = ui->rotacaoPontoY->text().toDouble();
    emit sRotacionarNoPonto(teta,pX,pY);
}

void Transformacoes::rotacionar2D(){
    if(ui->radioButton->isChecked())
        rotacionarNaOrigem2D();
    if(ui->radioButton_2->isChecked())
        rotacionarNoCentro2D();
    if(ui->radioButton_3->isChecked())
        rotacionarNoPonto2D();
}

void Transformacoes::escolherCor()
{
    QColor cor = QColorDialog::getColor(Qt::black, this);
    scene->setBackgroundBrush(QBrush(cor));
}

void Transformacoes::mudarCor()
{
    emit sMudarCor(scene->backgroundBrush().color());
}

