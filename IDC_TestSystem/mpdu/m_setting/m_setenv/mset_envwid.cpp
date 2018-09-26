/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mset_envwid.h"
#include "ui_mset_envwid.h"

MSet_EnvWid::MSet_EnvWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSet_EnvWid)
{
    ui->setupUi(this);
    initWid();
}

MSet_EnvWid::~MSet_EnvWid()
{
    delete ui;
}


void MSet_EnvWid::initWid()
{
    int id = 0;
    mWid[id] = new MSet_EnvUnitWid(ui->temGroup);
    mWid[id++]->initWid(0, Mpdu_Rtu_Test_min);

    mWid[id] = new MSet_EnvUnitWid(ui->humGroup);
    mWid[id++]->initWid(1, Mpdu_Rtu_Test_min);

    mSnmp = new MSet_SnmpThread(this);
    connect(mSnmp,SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));

    mRtu = new MSet_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void MSet_EnvWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void MSet_EnvWid::sendSnmp(int addr)
{
    QList<sSnmpSetCmd> list;
    for(int i=0; i<2; ++i) {
        mWid[i]->getCmdList(i , addr, list);
    }

    for(int i=0; i<list.size(); ++i) {
        mSnmp->setCmd(list.at(i));
    }
}

void MSet_EnvWid::sendRtu(int addr)
{
    QList<sRtuSetCmd> list;
    for(int i=0; i<2; ++i) {
        mWid[i]->getCmdList(addr, list);
    }

    for(int i=0; i<list.size(); ++i) {
        mRtu->setCmd(list.at(i));
    }
}

void MSet_EnvWid::on_pushButton_clicked()
{

    int addr = ui->spinBox->value();

    sConfigItem *item = M_ConfigFile::bulid()->item;
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
