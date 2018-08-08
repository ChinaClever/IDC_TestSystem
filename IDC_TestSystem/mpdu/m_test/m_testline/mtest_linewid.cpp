/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mtest_linewid.h"
#include "ui_mtest_linewid.h"

MTest_LineWid::MTest_LineWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MTest_LineWid)
{
    ui->setupUi(this);
    initWid();
}

MTest_LineWid::~MTest_LineWid()
{
    delete ui;
}


void MTest_LineWid::initWid()
{
    int id = 0;
    mWid[id] = new MTest_LineUnitWid(ui->volGroup);
    mWid[id++]->initWid(1, Mpdu_Rtu_Test_min);

    mWid[id] = new MTest_LineUnitWid(ui->curGroup);
    mWid[id++]->initWid(0, Mpdu_Rtu_Test_min);

    mWid[id] = new MTest_LineUnitWid(ui->groupBox);
    mWid[id++]->initWid(0, Mpdu_Rtu_Test_crMin);

    mRtu = new MTest_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void MTest_LineWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}


void MTest_LineWid::on_pushButton_clicked()
{
    QList<sMTestRtuSetCmd> list;
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
