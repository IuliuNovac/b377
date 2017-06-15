#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include <QLCDNumber>
#include <QSerialPort>

QSerialPort *serial;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
   ui->setupUi(this);
   ui->setupUi(this);
   serial = new QSerialPort(this);
   serial->setPortName("COM3");
   serial->open(QIODevice::ReadOnly);
   serial->setBaudRate(QSerialPort::Baud9600);
   serial->setDataBits(QSerialPort::Data8);
   serial->setParity(QSerialPort::NoParity);
   serial->setStopBits(QSerialPort::OneStop);
   serial->setFlowControl(QSerialPort::NoFlowControl);
   connect(serial,SIGNAL(readyRead()),this,SLOT(serialReceived()));

}

Dialog::~Dialog()
{
    delete ui;
    serial->close();
}

void Dialog::serialReceived()
{
    QByteArray serialData = serial->readAll();
    input = QString::fromStdString(serialData.toStdString());
    ui->lcdNumber->display(input);


}
