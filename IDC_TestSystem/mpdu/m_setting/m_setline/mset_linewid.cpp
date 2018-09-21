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

    mRtu = new MSet_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void MSet_LineWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}


void MSet_LineWid::on_pushButton_clicked()
{
    QList<sRtuSetCmd> list;
    int addr = ui->spinBox->value();

    for(int i=0; i<3; ++i) {
       mWid[i]->getCmdList(addr, list);
    }

    for(int i=0; i<list.size(); ++i) {
         mRtu->setCmd(list.at(i));
    }

    mRtu->start();
    ui->textEdit->clear();
}
