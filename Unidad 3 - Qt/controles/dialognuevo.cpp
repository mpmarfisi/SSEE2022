#include "dialognuevo.h"
#include "ui_dialognuevo.h"

DialogNuevo::DialogNuevo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNuevo)
{
    ui->setupUi(this);
}

DialogNuevo::~DialogNuevo()
{
    delete ui;
}
