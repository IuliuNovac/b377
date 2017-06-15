#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLCDNumber>
#include <QMainWindow>
#include <QSerialPort>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    QString input;

private slots:
   void serialReceived();

private:
   Ui::Dialog *ui;

   QSerialPort *serial;
   Dialog *secDialog;
   QLCDNumber *sr;

};

#endif // DIALOG_H
