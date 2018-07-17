/*
 *
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    mBusWid = new BUS_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mBusWid);

    mSiWid = new SIMainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSiWid);

    mMpduWid = new MPDU_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mMpduWid);

    mIpWid = new IP_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mIpWid);
}

void MainWindow::on_sipduBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mSiWid);
}

void MainWindow::on_siBusBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mBusWid);
}

void MainWindow::on_mpduBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mMpduWid);
}

void MainWindow::on_ippduBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mIpWid);
}
