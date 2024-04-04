#include "nota.h"
#include "ui_nota.h"
#include "utils.h"
#define archivo "C:\\Data\\Asignaturas.xml"

nota::nota(QStringList &asignaturas, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::nota)
{
    ui->setupUi(this);
    ui->comboBox->addItems(asignaturas);

}

nota::~nota()
{
    delete ui;
}

void nota::on_btnAceptar_clicked()
{
    qualificacion = ui->nnota->text();
    modificarXML(archivo, asignatura, "NOTA", qualificacion);
    this->close();

}


void nota::on_comboBox_currentTextChanged(const QString &arg1)
{
    asignatura = arg1;
    qDebug() << asignatura;
}

