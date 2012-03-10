#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "dialog.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void abrirJanela();
    void drawDot(int,int);
    void drawLine(int,int,int,int);

private:
    Ui::MainWindow *ui;
    Dialog *newObjectWindow;
    QGraphicsScene * viewport;
};

#endif // MAINWINDOW_H
