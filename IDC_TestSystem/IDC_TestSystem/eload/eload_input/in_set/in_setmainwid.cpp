/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "in_setmainwid.h"
#include "ui_in_setmainwid.h"
#include "common.h"
IN_setMainWid::IN_setMainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IN_setMainWid)
{
    ui->setupUi(this);

    groupBox_background_icon(this);
    mSetEnvWid = new IN_SetEnvWid(ui->groupBox_3) ;
    mSetThresholdWid = new IN_SetThresholdWid(ui->groupBox_2);
}

IN_setMainWid::~IN_setMainWid()
{
    delete ui;
}
