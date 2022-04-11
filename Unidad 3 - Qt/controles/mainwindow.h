#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnEnviar_clicked();

    void on_btnCargarImagen_clicked();

    void on_actionMenu_1_triggered();

    void on_btnCambiarModo_clicked();

    void on_pushButton_clicked();

    void on_btnVerValor_clicked();

    void on_dial_sliderMoved(int position);

    void on_dial_valueChanged(int value);

    void on_dtFecha_dateChanged(const QDate &date);

    void on_actionUn_submenu_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
