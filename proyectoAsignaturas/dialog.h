#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QStringList &asignaturas, QWidget *parent = nullptr);
    ~Dialog();

private slots:


    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_btAceptar_clicked();

private:
    Ui::Dialog *ui;
    QString asignatura;
};

#endif // DIALOG_H
