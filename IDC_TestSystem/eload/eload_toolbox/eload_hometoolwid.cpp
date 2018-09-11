/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "eload_hometoolwid.h"
#include "ui_eload_hometoolwid.h"

ELoad_HomeToolWid::ELoad_HomeToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELoad_HomeToolWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

ELoad_HomeToolWid::~ELoad_HomeToolWid()
{
    delete ui;
}

void ELoad_HomeToolWid::on_homeBtn_clicked()
{
    emit toolSig(ELoad_Info_Home);
}
