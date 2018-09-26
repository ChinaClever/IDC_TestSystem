/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mset_linewid.h"
#include "ui_mset_linewid.h"

MSet_LineWid::MSet_LineWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSet_LineWid)
{
    ui->setupUi(this);
    initWid();
}

MSet_LineWid::~MSet_LineWid()
{
    delete ui;
}


void MSet_LineWid::initWid()
{
    int id = 0;
    mWid[id] = new MSet_LineUnitWid(ui->volGroup);
    mWid[id++]->initWid(1, Mpdu_Rtu_Test_min);

    mWid[id] = new MSet_LineUnitWid(ui->curGroup);
    mWid[id++]->initWid(0, Mpdu_Rtu_Test_min);

    mWid[id] = new MSet_LineUnitWid(ui->groupBox);
    mWid[id++]->initWid(0, Mpdu_Rtu_Test_crMin);

    mSnmp = new MSet_SnmpThread(this);
    connect(mSnmp, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));

    mRtu = new MSet_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void MSet_LineWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void MSet_LineWid::sendSnmp(int addr)
{
    QList<sSnmpSetCmd> list;
    for(int i=0; i<3; ++i) {
        mWid[i]->getCmdList(i , addr, list);
    }

    for(int i=0; i<list.size(); ++i) {
        mSnmp->setCmd(list.at(i));
    }
}

void MSet_LineWid::sendRtu(int addr)
{
    QList<sRtuSetCmd> list;
    for(int i=0; i<3; ++i) {
        mWid[i]->getCmdList(addr, list);
    }

    for(int i=0; i<list.size(); ++i) {
        mRtu->setCmd(list.at(i));
    }
}
void MSet_LineWid::on_pushButton_clicked()
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
