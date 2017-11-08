/*
 *
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialportwid.h"
#include "si_rtu/si_rtuthread.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SerialPortWid *wid = new SerialPortWid(ui->widget);

    SI_RtuThread *rtuThread =  SI_RtuThread::bulid(this);
    rtuThread->init(wid->getSerialPort());


}

MainWindow::~MainWindow()
{
    delete ui;
}
