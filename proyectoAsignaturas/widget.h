#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void cargaDatos(QStringList asignaturas, int index);
    QStringList leerFicher(const QString &archivo);
    void inicializaTablas();
    ~Widget();

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_btIntroducir_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
