#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <list>
#include "figura.h"

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

public slots:
    void desenharReta();
    void desenharPonto();
    void adicionarPonto();
    void desenharPoligono();

signals:
    void desenharFigura(Tipo, list<Ponto*>);

private:
    Ui::Dialog *ui;
    list<Ponto*> pontos;
};

#endif // DIALOG_H
