/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "eload_homemainwid.h"
#include "ui_eload_homemainwid.h"
#include "common.h"
ELoad_HomeMainWid::ELoad_HomeMainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELoad_HomeMainWid)
{
    ui->setupUi(this);

    groupBox_background_icon(this);
    mStatusWid = new ELoad_StatusHomeWid(ui->widget_1);
    mInputWid = new ELoad_InputHomeWid(ui->widget_2);
    connect(mStatusWid,SIGNAL(updateIndexSig(int,QString)),mInputWid,SLOT(updateIndexSlot(int,QString)));
    connect(mStatusWid,SIGNAL(sendResistanceCmdSig(int,int,int)),mInputWid,SLOT(recvResistanceCmdSlot(int,int,int)));
    connect(mInputWid,SIGNAL(sendResFinishSig()),mStatusWid,SLOT(sendResFinishSlot()));
}

ELoad_HomeMainWid::~ELoad_HomeMainWid()
{
    delete ui;
}
