/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "eload_inputtoolwid.h"
#include "ui_eload_inputtoolwid.h"

ELoad_InputToolWid::ELoad_InputToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELoad_InputToolWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
}

ELoad_InputToolWid::~ELoad_InputToolWid()
{
    delete ui;
}

void ELoad_InputToolWid::on_realBtn_clicked()
{
     emit toolSig(ELoad_Info_Input);
}

void ELoad_InputToolWid::on_thresholdBtn_clicked()
{
    emit toolSig(ELoad_Info_InputThreshold);
}

void ELoad_InputToolWid::on_transBtn_clicked()
{
    emit toolSig(ELoad_Info_Trans);
}

void ELoad_InputToolWid::on_envBtn_clicked()
{
    emit toolSig(ELoad_Info_Env);
}

void ELoad_InputToolWid::on_setBtn_clicked()
{
     emit toolSig(ELoad_Info_Set);
}
