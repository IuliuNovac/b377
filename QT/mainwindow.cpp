#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QMessageBox>
#include <QSerialPort>
#include <QDebug>
#include <QSerialPortInfo>
#include <QIODevice>



MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
ui->setupUi(this);
 }

MainWindow::~MainWindow()
{
delete ui;

}



void MainWindow::on_button_clicked()
{
   hide();
    secDialog = new Dialog(this);
    secDialog->show();

}


void MainWindow::on_pushButton_clicked()
{
    hide();
newAbout = new about(this);
newAbout->show();
}
