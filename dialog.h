#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <list>
#include "ponto.h"

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
    void drawLine();
    void drawDot();
    void addPoint();
    void drawPolygon();

signals:
    void drawLineM(double, double, double, double);
    void drawDotM(double, double);
    void drawPolygonM(list<Ponto*>);

private:
    Ui::Dialog *ui;
    list<Ponto*> pontos;
};

#endif // DIALOG_H
