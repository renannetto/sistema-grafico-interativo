#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

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

signals:
    void drawLineM(double, double, double, double);
    void drawDotM(double, double);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
