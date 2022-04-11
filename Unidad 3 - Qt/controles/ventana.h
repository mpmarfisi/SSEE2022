#ifndef VENTANA_H
#define VENTANA_H

#include <QDialog>

namespace Ui {
class Ventana;
}

class Ventana : public QDialog
{
    Q_OBJECT

public:
    explicit Ventana(QWidget *parent = 0);
    ~Ventana();
    void EstablecerTexto(QString);

private slots:
    void on_btnVolver_clicked();

private:
    Ui::Ventana *ui;
    QString texto;
};

#endif // VENTANA_H
