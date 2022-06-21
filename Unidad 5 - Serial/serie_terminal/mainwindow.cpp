#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    enumerarPuertos();
    //ui->pbEnviar->hide();
    ui->pbEnviar->setEnabled(false);

    connect(&puerto, SIGNAL(readyRead()), this, SLOT(on_datosRecibidos()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enumerarPuertos()
{
    ui->cbPuertos->clear(); // Limpio antes de actualizar la lista para que no se haga infinita
    QList<QSerialPortInfo> puertos = QSerialPortInfo::availablePorts();
    for(int i = 0; i < puertos.count(); i++)
    {
        ui->cbPuertos->addItem(puertos.at(i).portName());
    }
}

void MainWindow::on_pbActualizar_clicked()
{
    enumerarPuertos();
}

void MainWindow::on_pbConectar_clicked()
{
    if(!puerto.isOpen())
    {
        QString portName = ui->cbPuertos->currentText();
        puerto.setPortName(portName);
        puerto.setBaudRate(QSerialPort::Baud9600);
        puerto.setDataBits(QSerialPort::Data8);
        puerto.setParity(QSerialPort::NoParity);
        puerto.setStopBits(QSerialPort::OneStop);
        puerto.setFlowControl(QSerialPort::NoFlowControl);
        if(puerto.open(QIODevice::ReadWrite) == true)
        {
            ui->pbConectar->setText("Desconectar");
            ui->statusbar->showMessage(portName + " conectado OK", 5000); // Muestro msg en la status bar por un tiempo
            ui->pbEnviar->setEnabled(true); // Encapsular cambios en ui en funcion

        } else {
            QMessageBox::critical(this, "Error", "No se pudo abrir el puerto " + portName);
        }
    } else {
        puerto.close();
        ui->pbEnviar->setEnabled(false);
        ui->pbConectar->setText("Conectar");
        ui->statusbar->showMessage(puerto.portName() + " desconectado OK", 5000);
    }
}

void MainWindow::on_pbEnviar_clicked()
{
    QByteArray datos;
    char aux = 0;
    QString textEdit = ui->teTX->toPlainText();
    datos.append(textEdit);
    for(int i = 0; i < datos.size(); i++)
    {
        aux = datos.at(i);
        puerto.flush();
        puerto.write(&aux, 1);
    }

}

void MainWindow::on_datosRecibidos()
{
    QByteArray datos;
    int cant = puerto.bytesAvailable();
    datos.resize(cant);
    //datos = puerto.readAll(); // Retorna todo a un qbytearray
    puerto.read(datos.data(), cant);
    // Procesamiento de los datos recibidos
    QString textoRX(datos);
    ui->teRX->append(textoRX);
}

void MainWindow::on_pbClearTX_clicked()
{
    ui->teTX->clear();
}

void MainWindow::on_pbClearRX_clicked()
{
    ui->teRX->clear();
}
