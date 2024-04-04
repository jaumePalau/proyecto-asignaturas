#include "widget.h"
#include "main.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("Gestor de asignaturas");
    w.show();
    return a.exec();
}
