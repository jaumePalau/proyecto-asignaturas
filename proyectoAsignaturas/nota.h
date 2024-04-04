#ifndef NOTA_H
#define NOTA_H

#include <QDialog>

namespace Ui {
class nota;
}

class nota : public QDialog
{
    Q_OBJECT

public:
    explicit nota(QStringList &asignaturas, QWidget *parent = nullptr);
    ~nota();

private slots:
    void on_btnAceptar_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::nota *ui;
    QString qualificacion;
    QString asignatura;
};

#endif // NOTA_H
