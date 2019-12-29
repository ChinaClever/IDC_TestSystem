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

    mMpduV1Wid = new MPDUV1_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mMpduV1Wid);

    mZpduWid = new ZPDU_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mZpduWid);

    mIpWid = new IP_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mIpWid);

    mRpduWid = new RPDU_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mRpduWid);

    this->setButtonColor(ui->eloadBtn);
}

void MainWindow::on_sipduBtn_clicked()
{
    this->setButtonColor(ui->sipduBtn);
    ui->stackedWid->setCurrentWidget(mSiWid);
}

void MainWindow::on_siBusBtn_clicked()
{
    this->setButtonColor(ui->siBusBtn);
    ui->stackedWid->setCurrentWidget(mBusWid);
}

void MainWindow::on_mpduBtn_clicked()
{
    this->setButtonColor(ui->mpduBtn);
    ui->stackedWid->setCurrentWidget(mMpduWid);
}

void MainWindow::on_ippduBtn_clicked()
{
    this->setButtonColor(ui->ippduBtn);
    ui->stackedWid->setCurrentWidget(mIpWid);
}

void MainWindow::on_zpduBtn_clicked()
{
    this->setButtonColor(ui->zpduBtn);
     ui->stackedWid->setCurrentWidget(mZpduWid);
}

void MainWindow::on_eloadBtn_clicked()
{
    this->setButtonColor(ui->eloadBtn);
    ui->stackedWid->setCurrentWidget(mELoadWid);
}

void MainWindow::on_rpduBtn_clicked()
{
     this->setButtonColor(ui->rpduBtn);
     ui->stackedWid->setCurrentWidget(mRpduWid);
}

void MainWindow::on_mpduv1Btn_clicked()
{
     this->setButtonColor(ui->mpduv1Btn);
     ui->stackedWid->setCurrentWidget(mMpduV1Wid);
}

void MainWindow::setButtonColor(QPushButton *button)
{
    ui->eloadBtn->setStyleSheet("font: 12pt \"微软雅黑\";");
    ui->ippduBtn->setStyleSheet("font: 12pt \"微软雅黑\";");
    ui->zpduBtn->setStyleSheet("font: 12pt \"微软雅黑\";");
    ui->eloadBtn->setStyleSheet("font: 12pt \"微软雅黑\";");
    ui->rpduBtn->setStyleSheet("font: 12pt \"微软雅黑\";");
    ui->mpduv1Btn->setStyleSheet("font: 12pt \"微软雅黑\";");
    ui->mpduBtn->setStyleSheet("font: 12pt \"微软雅黑\";");
    ui->siBusBtn->setStyleSheet("font: 12pt \"微软雅黑\";");
    ui->sipduBtn->setStyleSheet("font: 12pt \"微软雅黑\";");

    button->setStyleSheet("background-color: rgb(96,238,250); font: 12pt \"微软雅黑\";");
}
