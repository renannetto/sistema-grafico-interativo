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
    void transladar();
    void escalonar();
    void rotacionar(int);
    void escolherCor();
    void mudarCor();

signals:
    void sTransladar(double,double);
    void sEscalonar(double,double);
    void sRotacionarNaOrigem(double, double, double, double);
    void sRotacionarNoCentro(double, double, double, double);
    void sRotacionarNoPonto(double,double,double, double, double, double, double);
    void sMudarCor(QColor cor);

private:
    void rotacionarNaOrigem(int);
    void rotacionarNoCentro(int);
    void rotacionarNoPonto(int);
    Ui::Transformacoes *ui;
    QGraphicsScene *scene;
    int posicaoAnteriorDoSlider;
};

#endif // TRANSFORMACOES_H
