#ifndef TRANSFORMACOES_H
#define TRANSFORMACOES_H

#include <QDialog>
#include <QGraphicsScene>
#include <QColorDialog>
#include <sstream>

using namespace std;

namespace Ui {
    class Transformacoes;
}

class Transformacoes : public QDialog
{
    Q_OBJECT

public:
    explicit Transformacoes(QWidget *parent = 0);
    ~Transformacoes();
    void receberPontoX(double);
    void receberPontoY(double);

private slots:
    void aumentarEscalonamentoX();
    void diminuirEscalonamentoX();
    void aumentarEscalonamentoY();
    void diminuirEscalonamentoY();
    void transladar2D();
    void escalonar2D();
    void rotacionar2D();
    void escolherCor();
    void mudarCor();

signals:
    void sTransladar2D(double,double);
    void sEscalonar2D(double,double);
    void sRotacionarNaOrigem(double);
    void sRotacionarNoCentro(double);
    void sRotacionarNoPonto(double,double,double);
    void sMudarCor(QColor cor);

private:
    void rotacionarNaOrigem2D();
    void rotacionarNoCentro2D();
    void rotacionarNoPonto2D();
    Ui::Transformacoes *ui;
    QGraphicsScene *scene;
};

#endif // TRANSFORMACOES_H
