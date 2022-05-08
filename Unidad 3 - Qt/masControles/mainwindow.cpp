#include "mainwindow.h"
#include "ui_mainwindow.h"

//para escribir archivos
#include <QTextDocumentWriter>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //escribo el titulo de la ventana
    setWindowTitle("Evaluacion de controles Parte II");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAgregar_clicked()
{
    //rutina para agregar elementos en la lista

    QString aux = ui->txtCampo->text();

    //evaluo si el campo está vacío antes de cargarlo
    if(aux != "")
    {
        //ui->lstListado->selectedItems()

        //como el elemento es distinto de null lo agrego
        ui->lstListado->addItem(aux);

        //obtengo la cantidad de elementos
        int cant = ui->lstListado->count();

        //lo muestro en un campo de texto
        ui->txtCantidad->setText(QString::number(cant));

    }
}

void MainWindow::on_btnBorrar_clicked()
{
    //borro los elementos de la lista

    for(int a = 0 ; a < ui->lstListado->count(); a++)
    {
                QListWidgetItem* item = ui->lstListado->takeItem(a);
                delete item;
    }



}

void MainWindow::on_lstListado_currentRowChanged(int currentRow)
{
    //sobre el elemento seleccionado, lo muestro en un campo de texto

    QString aux = ui->lstListado->item(currentRow)->text();

    ui->txtItemElegido->setText(aux);

}

void MainWindow::on_lstListado_activated(const QModelIndex &index)
{

}

void MainWindow::on_btnAbrir_clicked()
{
    //abro un cuadro de dialogo para elegir ubicación y nombre
    QString fn = QFileDialog::getOpenFileName(this, tr("Abrir archivo..."), QString(), tr("Archivos de texto (*.txt);;Todos los archivos (*)"));

    //pregunto si es valido
    if (!fn.isEmpty())
    {
        //cargo el nombre del archivo en el campo de texto
        ui->txtArchivo->setText(fn);

        //leo archivo
        QFile file(fn);

        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);

        //leo todo el texto
        QString texto = in.readAll();

        //cargo el contenido en el control
        ui->txtMiTexto->setPlainText(texto);

        //cierro archivo
        file.close();

    }
}

void MainWindow::on_btnGuardar_clicked()
{
    //abro un cuadro de dialogo para elegir ubicación y nombre
    QString fn = QFileDialog::getSaveFileName(this, tr("Guardar archiv..."), QString(), tr("Archivos de texto (*.txt)"));

    //pregunto si es valido
    if(!fn.isEmpty())
    {

            QTextDocumentWriter writer(fn);

            //escribo el archivo
            writer.write(ui->txtMiTexto->document());


    }
}
