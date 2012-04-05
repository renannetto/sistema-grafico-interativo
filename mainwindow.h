#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <string>
#include <iostream>
#include <math.h>
#include "Clipping.h"
#include "canvas.h"
#include "dialog.h"
#include "Transformacoes.h"
#include "windowviewport.h"


namespace Ui {
    class MainWindow;
}

using namespace std;

static double const VIEWPORTXSIZE = 660;
static double const VIEWPORTYSIZE = 500;
static double const SUBVIEWPORTXMIN = 20;
static double const SUBVIEWPORTXMAX = 639;
static double const SUBVIEWPORTYMIN = 20;
static double const SUBVIEWPORTYMAX = 479;

class Canvas;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void reiniciar();
    void resetarWindow();
    void abrirJanelaDeCriacoes();
    void abrirJanelaDeTransformacoes();
    void abrirJanelaDeAjuda();
    void construirFigura(Tipo, list<Ponto*>, QColor);
    void destruirFigura();
    void receberPonto(double, double);
    void zoomIn();
    void zoomOut();
    void mostrarValorDoZoom(int);
    void moverParaEsquerda();
    void moverParaDireita();
    void moverParaCima();
    void moverParaBaixo();
    void transladar2D(double,double);
    void escalonar2D(double,double);
    void rotacionarNaOrigem2D(double);
    void rotacionarNoCentro2D(double);
    void rotacionarNoPonto2D(double,double,double);
    void mudarCor(QColor cor);
    void rotacionarWindowParaDireita();
    void rotacionarWindowParaEsquerda();

private:
    void iniciar();
    void desenharFiguras();
    void desenharSubViewport();
    double transformadaViewportX(double);
    double transformadaViewportY(double);
    double transformadaInversaViewportX(double);
    double transformadaInversaViewportY(double);
    WindowViewport *windowViewport;
    Ui::MainWindow *ui;
    QGraphicsScene *viewport;
    Dialog *janelaDeCriacoes;
    Transformacoes *janelaDeTransformacoes;
    Canvas *detectorDeEventos;
    Clipping *clipador;
    int deslocamentoClipador;
};

#endif // MAINWINDOW_H
