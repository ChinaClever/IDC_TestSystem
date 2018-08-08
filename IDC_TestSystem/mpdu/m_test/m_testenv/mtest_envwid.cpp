/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mtest_envwid.h"
#include "ui_mtest_envwid.h"

MTest_EnvWid::MTest_EnvWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MTest_EnvWid)
{
    ui->setupUi(this);
    initWid();
}

MTest_EnvWid::~MTest_EnvWid()
{
    delete ui;
}


void MTest_EnvWid::initWid()
{
    int id = 0;
    mWid[id] = new MTest_EnvUnitWid(ui->temGroup);
    mWid[id++]->initWid(0, Mpdu_Rtu_Test_min);

    mWid[id] = new MTest_EnvUnitWid(ui->humGroup);
    mWid[id++]->initWid(1, Mpdu_Rtu_Test_min);

    mRtu = new MTest_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void MTest_EnvWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}


void MTest_EnvWid::on_pushButton_clicked()
{
    QList<sMTestRtuSetCmd> list;
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
