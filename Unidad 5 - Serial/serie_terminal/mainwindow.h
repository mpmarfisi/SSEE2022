#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_pbActualizar_clicked();

    void on_pbConectar_clicked();

    void on_pbEnviar_clicked();

    void on_datosRecibidos();

    void on_pbClearTX_clicked();

    void on_pbClearRX_clicked();

private:
    void enumerarPuertos();

    Ui::MainWindow *ui;
    QSerialPort puerto;
};
#endif // MAINWINDOW_H
