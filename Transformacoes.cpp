#include "Transformacoes.h"
#include "ui_Transformacoes.h"

Transformacoes::Transformacoes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transformacoes)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    posicaoAnteriorDoSlider = ui->dial->value();
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

void Transformacoes::transladar(){
    double qtd = ui->qtdTranslacao->text().toDouble();
    double vX = (double)ui->translacaoX->value()*qtd/100;
    double vY = (double)ui->translacaoY->value()*qtd/100;
    double vZ = (double)ui->translacaoZ->value()*qtd/100;
    emit sTransladar(vX,vY,vZ);
}

void Transformacoes::escalonar(){
    double qtd = ui->qtdEscalonamento->text().toDouble();
    double vX = (double)ui->escalonamentoX->value()*(qtd-1)/100 + 1;
    double vY = (double)ui->escalonamentoY->value()*(qtd-1)/100 + 1;
    double vZ = (double)ui->escalonamentoZ->value()*(qtd-1)/100 + 1;
    emit sEscalonar(vX,vY,vZ);
}

void Transformacoes::rotacionarNaOrigem(int angulo){
    double teta = (double) angulo;
    double ux = ui->eixoXEdit->text().toDouble();
    double uy = ui->eixoYEdit->text().toDouble();
    double uz = ui->eixoZEdit->text().toDouble();
    emit sRotacionarNaOrigem(teta, ux, uy, uz);
}

void Transformacoes::rotacionarNoCentro(int angulo){
    double teta = (double) angulo;
    double ux = ui->eixoXEdit->text().toDouble();
    double uy = ui->eixoYEdit->text().toDouble();
    double uz = ui->eixoZEdit->text().toDouble();
    emit sRotacionarNoCentro(teta, ux, uy, uz);
}

void Transformacoes::rotacionarNoPonto(int angulo){
    double teta = (double) angulo;
    double ux = ui->eixoXEdit->text().toDouble();
    double uy = ui->eixoYEdit->text().toDouble();
    double uz = ui->eixoZEdit->text().toDouble();
    double pX = ui->rotacaoPontoX->text().toDouble();
    double pY = ui->rotacaoPontoY->text().toDouble();
    double pZ = ui->rotacaoPontoZ->text().toDouble();
    emit sRotacionarNoPonto(teta, pX, pY, pZ, ux, uy, uz);
}

void Transformacoes::rotacionar(int anguloA){
    int angulo = anguloA - posicaoAnteriorDoSlider;
    if(ui->radioButton->isChecked())
        rotacionarNaOrigem(angulo);
    if(ui->radioButton_2->isChecked())
        rotacionarNoCentro(angulo);
    if(ui->radioButton_3->isChecked())
        rotacionarNoPonto(angulo);
    posicaoAnteriorDoSlider = anguloA;
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
