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

void Transformacoes::transladar(){
    double vX = ui->deslocamentoXEdit->text().toDouble();
    double vY = ui->deslocamentoYEdit->text().toDouble();
    emit sTransladar(vX,vY);
}

void Transformacoes::escalonar(){
    double vX = ui->escalonamentoXEdit->text().toDouble();
    double vY = ui->escalonamentoYEdit->text().toDouble();
    emit sEscalonar(vX,vY);
}

void Transformacoes::rotacionarNaOrigem(){
    double teta = ui->anguloRotacao->text().toDouble();
    double ux = ui->eixoXEdit->text().toDouble();
    double uy = ui->eixoYEdit->text().toDouble();
    double uz = ui->eixoZEdit->text().toDouble();
    emit sRotacionarNaOrigem(teta, ux, uy, uz);
}

void Transformacoes::rotacionarNoCentro(){
    double teta = ui->anguloRotacao->text().toDouble();
    double ux = ui->eixoXEdit->text().toDouble();
    double uy = ui->eixoYEdit->text().toDouble();
    double uz = ui->eixoZEdit->text().toDouble();
    emit sRotacionarNoCentro(teta, ux, uy, uz);
}

void Transformacoes::rotacionarNoPonto(){
    double teta = ui->anguloRotacao->text().toDouble();
    double ux = ui->eixoXEdit->text().toDouble();
    double uy = ui->eixoYEdit->text().toDouble();
    double uz = ui->eixoZEdit->text().toDouble();
    double pX = ui->rotacaoPontoX->text().toDouble();
    double pY = ui->rotacaoPontoY->text().toDouble();
    double pZ = ui->rotacaoPontoZ->text().toDouble();
    emit sRotacionarNoPonto(teta, pX, pY, pZ, ux, uy, uz);
}

void Transformacoes::rotacionar(){
    if(ui->radioButton->isChecked())
        rotacionarNaOrigem();
    if(ui->radioButton_2->isChecked())
        rotacionarNoCentro();
    if(ui->radioButton_3->isChecked())
        rotacionarNoPonto();
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

void Transformacoes::aumentarEscalonamentoX(){
    stringstream novoValor;
    novoValor << ui->escalonamentoXEdit->text().toDouble()+0.1;
    ui->escalonamentoXEdit->setText(novoValor.str().c_str());
}

void Transformacoes::diminuirEscalonamentoX(){
    stringstream novoValor;
    novoValor << ui->escalonamentoXEdit->text().toDouble()-0.1;
    ui->escalonamentoXEdit->setText(novoValor.str().c_str());
}

void Transformacoes::aumentarEscalonamentoY(){
    stringstream novoValor;
    novoValor << ui->escalonamentoYEdit->text().toDouble()+0.1;
    ui->escalonamentoYEdit->setText(novoValor.str().c_str());
}

void Transformacoes::diminuirEscalonamentoY(){
    stringstream novoValor;
    novoValor << ui->escalonamentoYEdit->text().toDouble()-0.1;
    ui->escalonamentoYEdit->setText(novoValor.str().c_str());
}


