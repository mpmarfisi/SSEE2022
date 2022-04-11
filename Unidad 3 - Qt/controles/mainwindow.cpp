#include "mainwindow.h"
#include "ui_mainwindow.h"

// agrego los .h para debug o informar a usuario
#include "qmessagebox.h"

//agrego el .h correspondiente a la clase que alberga la nueva ventana
#include "ventana.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Establezco el titulo que le quiero dar a mi ventana principal

    this->setWindowTitle("Mi primera ventana");

    // Establezco rangos dial y barra
    int max = ui->dial->maximum();
    int min = ui->dial->minimum();

    ui->pbMiBarra->setMaximum(max);
    ui->pbMiBarra->setMinimum(min);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnEnviar_clicked()
{

    //Obtengo el texto cargado por el usuario
    QString aux = ui->txtaEnviar->text();


    //genero una instancia de la clase Ventana
    Ventana miVentana(this); // Le paso el parent que es this (seria la main window)

    //invoco al método EstablecerTexto y le paso como argumento el contenido de mi campo de texto
    miVentana.EstablecerTexto(aux);

    //establezco un titulo para miVentana
    miVentana.setWindowTitle("Titulo de mi ventana");

    //visualizo la ventana y pregunto por el código devuelto
    // para mas información ver el código del botón Volver dentro de miVentana
    if(miVentana.exec() == QDialog::Accepted) // Si pongo QDialog::Rejected seria el evento de apretar la cruz
    {

        // TO-DO es decir lo que quieran hacer

        // utilizo un QMessageBox para informar al usuario
        QMessageBox::information(this,tr("Titulo de prueba"),tr("Mi texto de prueba"));

    }

}

void MainWindow::on_btnCargarImagen_clicked()
{
    int alto =  ui->btnMiImagen->size().height();
    int ancho = ui->btnMiImagen->size().width();

    //tamaño fijo
    //ui->btnMiImagen->setIconSize(((QSize(200,200))));

    //tamaño de acuerdo al boton
    ui->btnMiImagen->setIconSize(QSize(ancho,alto));


    QPixmap* pixmap1 = new QPixmap(":/misRecursos/logo");
    QIcon icon1(*pixmap1);
    ui->btnMiImagen->setIcon(icon1);

}

void MainWindow::on_actionMenu_1_triggered()
{
    //genero un mensaje cuando se hace click sobre el menu
    QMessageBox::information(this,tr("Acceso a menu"),tr("accedi a mi opción"));
}

void MainWindow::on_btnCambiarModo_clicked()
{

    //si está tildado ajusto la orientación de la barra

    if( ui->chkModo->checkState() == Qt::Checked)
    {
        //orientación
        ui->pbMiBarra->setOrientation(Qt::Vertical);

        //modifico su tamaño
        ui->pbMiBarra->setFixedHeight(100);
        ui->pbMiBarra->setFixedWidth(20);

    }
    else
    {
        //orientación
        ui->pbMiBarra->setOrientation(Qt::Horizontal);

        //modifico su tamaño
        ui->pbMiBarra->setFixedHeight(30);
        ui->pbMiBarra->setFixedWidth(200);

    }


}

void MainWindow::on_pushButton_clicked()
{
    QString aux = ui->dtFecha->text();
    ui->lblFecha->setText(aux);
}

void MainWindow::on_btnVerValor_clicked()
{
    int valor = ui->dial->value();

    ui->lblFecha->setText(QString::number(valor));
}

void MainWindow::on_dial_sliderMoved(int position)
{

}

void MainWindow::on_dial_valueChanged(int value)
{
    int valor = value;
    ui->pbMiBarra->setValue(valor);
}

void MainWindow::on_dtFecha_dateChanged(const QDate &date)
{
    ui->lblFecha->setText(date.toString(Qt::TextDate));
}

void MainWindow::on_actionUn_submenu_triggered()
{
    //genero un mensaje cuando se hace click sobre el menu
    QMessageBox::information(this,tr("Acceso a submenu"),tr("accedi a mi opción de submenu"));
}
