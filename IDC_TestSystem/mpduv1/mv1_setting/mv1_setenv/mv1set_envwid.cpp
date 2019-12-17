/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1set_envwid.h"
#include "ui_mv1set_envwid.h"

MV1Set_EnvWid::MV1Set_EnvWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MV1Set_EnvWid)
{
    ui->setupUi(this);
    initWid();
}

MV1Set_EnvWid::~MV1Set_EnvWid()
{
    delete ui;
}


void MV1Set_EnvWid::initWid()
{
    int id = 0;
    mWid[id] = new MV1Set_EnvUnitWid(ui->temGroup);
    mWid[id++]->initWid(0, Mpdu_Rtu_Test_min);

    mWid[id] = new MV1Set_EnvUnitWid(ui->humGroup);
    mWid[id++]->initWid(1, Mpdu_Rtu_Test_min);

    mSnmp = new MV1Set_SnmpThread(this);
    connect(mSnmp,SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));

    mRtu = new MV1Set_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void MV1Set_EnvWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void MV1Set_EnvWid::sendSnmp(int addr)
{
    QList<sSnmpSetCmd> list;
    for(int i=0; i<2; ++i) {
        mWid[i]->getCmdList(i , addr, list);
    }

    for(int i=0; i<list.size(); ++i) {
        mSnmp->setCmd(list.at(i));
    }
}

void MV1Set_EnvWid::sendRtu(int addr)
{
    QList<sRtuSetCmd> list;
    for(int i=0; i<2; ++i) {
        mWid[i]->getCmdList(addr, list);
    }

    for(int i=0; i<list.size(); ++i) {
        mRtu->setCmd(list.at(i));
    }
}

void MV1Set_EnvWid::on_pushButton_clicked()
{

    int addr = ui->spinBox->value();

    sConfigItem *item = MV1_ConfigFile::bulid()->item;
    if(item->setMode == Test_SNMP)
    {
        sendSnmp(addr);
    }
    else
    {
        sendRtu(addr);
    }
    mSnmp->start();
    mRtu->start();
    ui->textEdit->clear();
}
