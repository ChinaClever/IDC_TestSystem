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
#include "testdlg.h"
#include "common.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //    SerialPortWid *wid = new SerialPortWid(ui->widget);

    //    SI_RtuThread *rtuThread =  SI_RtuThread::bulid(this);
    //    rtuThread->init(wid->getSerialPort());

    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
    set_background_icon(ui->widget,":/image/title_back.jpg");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initFunSLot()
{
    initWid();
}


void MainWindow::initWid()
{
    mSiWid = new SIMainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSiWid);

    mBusWid = new BUS_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mBusWid);
}

void MainWindow::on_sipduBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mSiWid);
}

void MainWindow::on_siBusBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mBusWid);
}
