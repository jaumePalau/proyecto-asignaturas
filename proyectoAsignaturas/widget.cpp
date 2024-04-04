#include "widget.h"
#include "ui_widget.h"
#include "dialog.h"
#include "nota.h"
#include <QLabel>
#include <QDebug>
#include <QStandardItemModel>
#include <QDialog>
#include "utils.h"
#define archivo "C:\\Data\\Asignaturas.xml"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);
    ui->tablaCom->setColumnWidth(0,250);
    ui->tablaCompleta->setColumnWidth(0,250);
    ui->tablaCur->setColumnWidth(0,250);
    ui->tablaPendiente->setColumnWidth(0,250);
    ui->tablaConvalidada->setColumnWidth(0,250);
    ui->tablaCursando->setColumnWidth(0,250);
    inicializaTablas();

    ui->tabWidget->setCurrentIndex(0);
}
void Widget:: inicializaTablas(){
    QStringList asignaturas = leerFicher(archivo);
    ui->tablaCompleta->setRowCount(0);
    cargaDatos(asignaturas,0);
    cargaDatos(buscarElementos(archivo, "Completa", "ESTADO", false), 1);
    cargaDatos(buscarElementos(archivo, "SI", "CURSADA", false),2);
    cargaDatos(buscarElementos(archivo, "Pendiente", "ESTADO", false),3);
    cargaDatos(buscarElementos(archivo, "C", "NOTA", false),4);
    cargaDatos(buscarElementos(archivo, "Cursando", "ESTADO", false),5);

}
void Widget:: cargaDatos(QStringList asignaturas, int index){
    if(index == 0){
        ui->tablaCompleta->clearContents();
        ui->tablaCompleta->setRowCount(0);
        for (int row = 0; row < asignaturas.size(); ++row) {
            ui->tablaCompleta->insertRow(ui->tablaCompleta->rowCount());

            QStringList rowData = asignaturas[row].split(", ");

            for (int col = 0; col < rowData.size(); ++col) {
                ui->tablaCompleta->setItem(row, col, new QTableWidgetItem(rowData[col]));

            }
        }
    }else if(index == 1){
        ui->tablaCom->clearContents();
        ui->tablaCom->setRowCount(0);
        for (int row = 0; row < asignaturas.size(); ++row) {
            ui->tablaCom->insertRow(ui->tablaCom->rowCount());
            QStringList rowData = asignaturas[row].split(", ");
            for (int col = 0; col < rowData.size(); ++col) {
                ui->tablaCom->setItem(row, col, new QTableWidgetItem(rowData[col]));
            }
        }
    }else if(index == 2){
        ui->tablaCur->clearContents();
        ui->tablaCur->setRowCount(0);
        for (int row = 0; row < asignaturas.size(); ++row) {
            ui->tablaCur->insertRow(ui->tablaCur->rowCount());
            QStringList rowData = asignaturas[row].split(", ");
            for (int col = 0; col < rowData.size(); ++col) {
                ui->tablaCur->setItem(row, col, new QTableWidgetItem(rowData[col]));
            }
        }
    }else if(index == 3){
        ui->tablaPendiente->clearContents();
        ui->tablaPendiente->setRowCount(0);
        for (int row = 0; row < asignaturas.size(); ++row) {
            ui->tablaPendiente->insertRow(ui->tablaPendiente->rowCount());
            QStringList rowData = asignaturas[row].split(", ");
            for (int col = 0; col < rowData.size(); ++col) {
                ui->tablaPendiente->setItem(row, col, new QTableWidgetItem(rowData[col]));
            }
        }
    }else if(index == 4){
        ui->tablaConvalidada->clearContents();
        ui->tablaConvalidada->setRowCount(0);
        for (int row = 0; row < asignaturas.size(); ++row) {
            ui->tablaConvalidada->insertRow(ui->tablaConvalidada->rowCount());
            QStringList rowData = asignaturas[row].split(", ");
            for (int col = 0; col < rowData.size(); ++col) {
                ui->tablaConvalidada->setItem(row, col, new QTableWidgetItem(rowData[col]));
            }
        }
    }else if(index == 5){
        ui->tablaCursando->clearContents();
        ui->tablaCursando->setRowCount(0);
        for (int row = 0; row < asignaturas.size(); ++row) {
            ui->tablaCursando->insertRow(ui->tablaCursando->rowCount());
            QStringList rowData = asignaturas[row].split(", ");
            for (int col = 0; col < rowData.size(); ++col) {
                ui->tablaCursando->setItem(row, col, new QTableWidgetItem(rowData[col]));
            }
        }
    }
}
QStringList Widget::leerFicher(const QString &data){
    QStringList asignaturas = leerXML(data);
    return asignaturas;
}
Widget::~Widget()
{
    delete ui;
}

void Widget::on_tabWidget_currentChanged(int index)
{
    qDebug() << "Tab index: " << index;
    /*switch(index){
    case 0:
        cargaDatos(leerFicher("C:\\Users\\psjau\\OneDrive\\Documentos\\Data\\Asignaturas.xml"),0);
        break;
    case 1:
        cargaDatos(buscarElementos("C:\\Users\\psjau\\OneDrive\\Documentos\\Data\\Asignaturas.xml", "Completa", "ESTADO"), 1);
        break;
    case 2:
        cargaDatos(buscarElementos("C:\\Users\\psjau\\OneDrive\\Documentos\\Data\\Asignaturas.xml", "SI", "CURSADA"),2);
        break;
    }*/
}


void Widget::on_btIntroducir_clicked()
{
    qDebug() << "Botón pulsado";
    QStringList asignaturas = buscarElementos(archivo, "Pendiente", "ESTADO", true);
    Dialog d(asignaturas, this);
    d.setWindowTitle("Cursar asignatura");
    d.exec();
    qDebug() << "Ventana cerrada";
    inicializaTablas();
}


void Widget::on_pushButton_clicked()
{
    qDebug() << "Botón pulsado";
    QStringList asignaturas = buscarElementos(archivo, "Cursando", "ESTADO", true);
    nota n(asignaturas, this);
    n.setWindowTitle("Añadir qualificación");
    n.exec();
    qDebug() << "Ventana cerrada";
    inicializaTablas();
}

