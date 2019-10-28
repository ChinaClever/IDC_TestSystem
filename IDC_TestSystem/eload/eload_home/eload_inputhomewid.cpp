/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "eload_inputhomewid.h"
#include "ui_eload_inputhomewid.h"
#include <QGridLayout>
ELoad_InputHomeWid::ELoad_InputHomeWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELoad_InputHomeWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
    initWid();
}

ELoad_InputHomeWid::~ELoad_InputHomeWid()
{
    delete ui;
}


void ELoad_InputHomeWid::initWid()
{
     QWidget *unitWid[3][8] = {{ui->widget_1, ui->widget_2, ui->widget_3, ui->widget_4, ui->widget_5, ui->widget_6, ui->widget_7, ui->widget_8},
                                      {ui->widget_9, ui->widget_10, ui->widget_11, ui->widget_12, ui->widget_13, ui->widget_14, ui->widget_15, ui->widget_16},
                                      {ui->widget_17, ui->widget_18, ui->widget_19, ui->widget_20, ui->widget_21, ui->widget_22, ui->widget_23, ui->widget_24}};
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<8; j++)
        {
            ELoad_InputUnitWid* wid = new ELoad_InputUnitWid(unitWid[i][j]);;
            mListPointer.append(wid);
            wid->init(i+1, j);
        }
    }
}

void ELoad_InputHomeWid::updateIndexSlot(int index,QString str)
{
    switch(index)
    {
    case 1: ui->groupBox->setTitle(tr("电子可控负载一")+str);
        break;
    case 2: ui->groupBox_2->setTitle(tr("电子可控负载二")+str);
        break;
    case 3: ui->groupBox_3->setTitle(tr("电子可控负载三")+str);
        break;
    default:
        ui->groupBox->setTitle(tr("电子可控负载一")+str);
        break;
    }
}

void ELoad_InputHomeWid::recvResistanceCmdSlot(int start,int end,int value)
{
    for(int i = start ; i <= end; i++)
    {
        mListPointer.at(i-1)->setResistance(i,value);
        Delay_MSec(10000);
    }
    emit sendResFinishSig();
}

