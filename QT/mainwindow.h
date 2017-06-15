#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QLCDNumber>
#include <QPushButton>
#include "dialog.h"
#include "about.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow //Derived class
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
        QString input;
    Ui::MainWindow *ui;
        Ui::Dialog *uii;

private slots:
    void on_button_clicked();

    void on_pushButton_clicked();

private:

    QSerialPort *serial;
    Dialog *secDialog;
    QLCDNumber *sr;
    about *newAbout;

};

#endif // MAINWINDOW_H
