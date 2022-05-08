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
    void on_btnAgregar_clicked();

    void on_btnBorrar_clicked();

    void on_lstListado_currentRowChanged(int currentRow);

    void on_lstListado_activated(const QModelIndex &index);

    void on_btnAbrir_clicked();

    void on_btnGuardar_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
