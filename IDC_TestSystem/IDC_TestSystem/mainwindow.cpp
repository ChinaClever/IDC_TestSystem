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

    QTimer::singleShot(5,this,SLOT(initFunSLot())); //延时初始化
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
    mELoadWid = new ELoad_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mELoadWid);

    mBusWid = new BUS_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mBusWid);

    mSiWid = new SIMainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSiWid);

    mMpduWid = new MPDU_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mMpduWid);

    mZpduWid = new ZPDU_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mZpduWid);

    mIpWid = new IP_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mIpWid);

    mRpduWid = new RPDU_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mRpduWid);
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

void MainWindow::on_zpduBtn_clicked()
{
     ui->stackedWid->setCurrentWidget(mZpduWid);
}

void MainWindow::on_eloadBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mELoadWid);
}

void MainWindow::on_rpduBtn_clicked()
{
    ui->stackedWid->setCurrentWidget(mRpduWid);
}
