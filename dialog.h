#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <list>
#include "figura.h"
#include <QColorDialog>
#include <QGraphicsScene>
#include <sstream>

using namespace std;

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void receberPontoX(double);
    void receberPontoY(double);

public slots:
    void desenharReta();
    void desenharPonto();
    void adicionarPonto();
    void desenharPoligono();
    void escolherCor();

signals:
    void desenharFigura(Tipo, list<Ponto*>, QColor cor);

private:
    Ui::Dialog *ui;
    list<Ponto*> pontos;
    QGraphicsScene *scene;
};

#endif // DIALOG_H
