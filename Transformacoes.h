#ifndef TRANSFORMACOES_H
#define TRANSFORMACOES_H

#include <QDialog>

namespace Ui {
    class Transformacoes;
}

class Transformacoes : public QDialog
{
    Q_OBJECT

public:
    explicit Transformacoes(QWidget *parent = 0);
    ~Transformacoes();

public slots:
    void transladar2D();
    void escalonar2D();
    void rotacionarNaOrigem2D();
    void rotacionarNoCentro2D();
    void rotacionarNoPonto2D();

signals:
    void sTransladar2D(double,double);
    void sEscalonar2D(double,double);
    void sRotacionarNaOrigem(double);
    void sRotacionarNoCentro(double);
    void sRotacionarNoPonto(double,double,double);

private:
    Ui::Transformacoes *ui;
};

#endif // TRANSFORMACOES_H
