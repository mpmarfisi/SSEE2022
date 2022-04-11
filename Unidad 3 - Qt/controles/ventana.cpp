#include "ventana.h"
#include "ui_ventana.h"

Ventana::Ventana(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ventana)
{
    ui->setupUi(this);
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::EstablecerTexto(QString textoEnviado)
{
    //recibo un texto y lo cargo en mi label
    //el label utiliza la nomenclatura "lbl + nombre"
    // esta nomenclatura no es obligatoria pero sirve para diferenciar el tipo de control
    ui->lblMiTexto->setText(textoEnviado);

}
void Ventana::on_btnVolver_clicked()
{
    //retorno al widget que me invoco
    accept();
}
