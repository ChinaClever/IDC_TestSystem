/*
 *
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialportwid.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SerialPortWid *wid = new SerialPortWid(ui->widget);

}

MainWindow::~MainWindow()
{
    delete ui;
}
