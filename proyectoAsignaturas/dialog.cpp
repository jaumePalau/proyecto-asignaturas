#include "dialog.h"
#include "ui_dialog.h"
#include "utils.cpp"

#define archivo "C:\\Data\\Asignaturas.xml"
Dialog::Dialog(QStringList &asignaturas, QWidget *parent)
    : QDialog(parent), ui(new Ui::Dialog)

{
    ui->setupUi(this);
    ui->comboBox->addItems(asignaturas);
    //connect(ui->pushButton, &QPushButton::clicked, this, &QDialog::close);

}

Dialog::~Dialog()
{
    delete ui;
}


void test(){
    qDebug() << "test";
}
void Dialog::on_comboBox_currentTextChanged(const QString &arg1)
{
    asignatura = arg1;
    qDebug() << asignatura;
    //modificarXML(archivo, asignatura, "ESTADO", "Cursando");
}



void Dialog::on_btAceptar_clicked()
{
    qDebug() << "Boton pulsado";
    modificarXML(archivo, asignatura, "ESTADO", "Cursando");
    this->close();
}

