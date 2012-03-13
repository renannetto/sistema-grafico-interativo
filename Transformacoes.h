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

private:
    Ui::Transformacoes *ui;
};

#endif // TRANSFORMACOES_H
