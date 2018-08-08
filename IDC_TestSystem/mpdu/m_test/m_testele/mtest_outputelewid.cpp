/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mtest_outputelewid.h"
#include "ui_mtest_outputelewid.h"

MTest_OutputEleWid::MTest_OutputEleWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MTest_OutputEleWid)
{
    ui->setupUi(this);
    mReg = 1030;
    initwid();
}

MTest_OutputEleWid::~MTest_OutputEleWid()
{
    delete ui;
}


void MTest_OutputEleWid::initwid()
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3, ui->widget_4, ui->widget_5,ui->widget_6,
                      ui->widget_7, ui->widget_8, ui->widget_9, ui->widget_10, ui->widget_11, ui->widget_12,
                      ui->widget_13,ui->widget_14, ui->widget_15, ui->widget_16,ui->widget_17,ui->widget_18,
                      ui->widget_19,ui->widget_20,ui->widget_21,ui->widget_22,ui->widget_23,ui->widget_24};

    for(int i=0; i<24; ++i) {
        mWid[i] = new MTest_EleItemWid(wid[i]);
        mWid[i]->init(i);
    }

    mRtu = new MTest_RtuThread(this);
    mRtu->mReg = mReg;
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}


void MTest_OutputEleWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void MTest_OutputEleWid::on_checkBox_clicked(bool checked)
{
    for(int i=0; i<24; ++i) {
        mWid[i]->setSelect(checked);
    }
}


void MTest_OutputEleWid::on_pushButton_clicked()
{
    for(int i=0; i<24; ++i) {
        if(mWid[i]->select()) {
            sMTestRtuSetCmd cmd;
            cmd.addr = ui->spinBox->value();
            cmd.reg = mReg + i;
            cmd.value = mWid[i]->status();
            mRtu->setCmd(cmd);
        }
    }

    mRtu->start();
    ui->textEdit->clear();
}


void MTest_OutputEleWid::on_cleanRadio_clicked(bool checked)
{
    for(int i=0; i<24; ++i) {
        mWid[i]->setClean(checked);
    }
}
