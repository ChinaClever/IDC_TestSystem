/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mpdurtutest_linewid.h"
#include "ui_mpdurtutest_linewid.h"

MpduRtuTest_LineWid::MpduRtuTest_LineWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MpduRtuTest_LineWid)
{
    ui->setupUi(this);
}

MpduRtuTest_LineWid::~MpduRtuTest_LineWid()
{
    delete ui;
}

void MpduRtuTest_LineWid::initWid(SerialPort *serial)
{
    int id = 0;
    mWid[id] = new MpduRtuTest_LineUnitWid(ui->volGroup);
    mWid[id++]->initWid(1, Mpdu_Rtu_Test_min);

    mWid[id] = new MpduRtuTest_LineUnitWid(ui->curGroup);
    mWid[id++]->initWid(0, Mpdu_Rtu_Test_min);

    mWid[id] = new MpduRtuTest_LineUnitWid(ui->groupBox);
    mWid[id++]->initWid(0, Mpdu_Rtu_Test_crMin);

    mRtu = new MpduRtuTestThread(this);
    mRtu->init(serial);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void MpduRtuTest_LineWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}


void MpduRtuTest_LineWid::on_pushButton_clicked()
{
    QList<sMpduRtuTestSetCmd> list;
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
