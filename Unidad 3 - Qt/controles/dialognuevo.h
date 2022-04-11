#ifndef DIALOGNUEVO_H
#define DIALOGNUEVO_H

#include <QDialog>

namespace Ui {
class DialogNuevo;
}

class DialogNuevo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNuevo(QWidget *parent = nullptr);
    ~DialogNuevo();

private:
    Ui::DialogNuevo *ui;
};

#endif // DIALOGNUEVO_H
