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

    mRtu = new MSet_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void MSet_EnvWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}


void MSet_EnvWid::on_pushButton_clicked()
{
    QList<sRtuSetCmd> list;
    int addr = ui->spinBox->value();

    for(int i=0; i<2; ++i) {
       mWid[i]->getCmdList(addr, list);
    }

    for(int i=0; i<list.size(); ++i) {
         mRtu->setCmd(list.at(i));
    }

    mRtu->start();
    ui->textEdit->clear();
}
