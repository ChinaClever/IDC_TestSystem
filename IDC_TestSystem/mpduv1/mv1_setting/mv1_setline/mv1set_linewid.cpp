/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1set_linewid.h"
#include "ui_mv1set_linewid.h"

MV1Set_LineWid::MV1Set_LineWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MV1Set_LineWid)
{
    ui->setupUi(this);
    initWid();
}

MV1Set_LineWid::~MV1Set_LineWid()
{
    delete ui;
}


void MV1Set_LineWid::initWid()
{
    int id = 0;
    mWid[id] = new MV1Set_LineUnitWid(ui->volGroup);
    mWid[id++]->initWid(1, Mpdu_Rtu_Test_min);

    mWid[id] = new MV1Set_LineUnitWid(ui->curGroup);
    mWid[id++]->initWid(0, Mpdu_Rtu_Test_min);

    mWid[id] = new MV1Set_LineUnitWid(ui->groupBox);
    mWid[id++]->initWid(0, Mpdu_Rtu_Test_crMin);

    mSnmp = new MV1Set_SnmpThread(this);
    connect(mSnmp, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));

    mRtu = new MV1Set_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void MV1Set_LineWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void MV1Set_LineWid::sendSnmp(int addr)
{
    QList<sSnmpSetCmd> list;
    for(int i=0; i<3; ++i) {
        mWid[i]->getCmdList(i , addr, list);
    }

    for(int i=0; i<list.size(); ++i) {
        mSnmp->setCmd(list.at(i));
    }
}

void MV1Set_LineWid::sendRtu(int addr)
{
    QList<sRtuSetCmd> list;
    for(int i=0; i<3; ++i) {
        mWid[i]->getCmdList(addr, list);
    }

    for(int i=0; i<list.size(); ++i) {
        mRtu->setCmd(list.at(i));
    }
}
void MV1Set_LineWid::on_pushButton_clicked()
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
