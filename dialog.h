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
    void construirReta();
    void construirPonto();
    void adicionarPontoPoligono();
    void construirPoligono();
    void adicionarPontoCurva();
    void construirCurva();
    void adicionarPontoPoliedro();
    void adicionarFacePoliedro();
    void construirPoliedro();
    void escolherCor();
    void limparTudo();

signals:
    void construirFigura(Tipo, list<Ponto*>, QColor cor);

private:
    Ui::Dialog *ui;
    list<Ponto*> pontosPoligono;
    list<Ponto*> pontosCurva;
    QGraphicsScene *scene;
};

#endif // DIALOG_H
