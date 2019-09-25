/*
 * 设置主窗口
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_setmainwid.h"
#include "ui_si_setmainwid.h"
#include "common.h"

SI_SetMainWid::SI_SetMainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SI_SetMainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    QTimer::singleShot(1000,this,SLOT(initFunSLot()));

    //    QGridLayout *gridLayout = new QGridLayout(parent);
    //    gridLayout->setContentsMargins(0, 0, 0, 0);
    //    gridLayout->addWidget(this);
}

SI_SetMainWid::~SI_SetMainWid()
{
    delete ui;
}

/**
 * @brief 延时初始化
 */
void SI_SetMainWid::initFunSLot()
{
    mData = new SI_Rtu_Recv();
    memset(mData, 0, sizeof(SI_Rtu_Recv));

    mAddrSetWid = new SI_AddrSetWid(ui->addrBox);
    mAddrSetWid->initPkt(mData);
    connect(mAddrSetWid, SIGNAL(updateSig(int)), this, SLOT(updateSlot(int)));

    mEleSetWid = new SI_EleSetWid(ui->eleBox);

    mThresholdSetWid[0] = new SI_ThresholdSetWid(ui->volBox);
    mThresholdSetWid[1] = new SI_ThresholdSetWid(ui->curBox);
    mThresholdSetWid[2] = new SI_ThresholdSetWid(ui->temBox);
    mThresholdSetWid[3] = new SI_ThresholdSetWid(ui->humBox);

    for(int i=0; i<4; ++i) {
        mThresholdSetWid[i]->init(SI_SetMode_Vol+i, mData->data);
        connect(mAddrSetWid, SIGNAL(updateSig(int)), mThresholdSetWid[i], SIGNAL(updateSig(int)));
    }

}

/**
 * @brief 更新
 * @param addr
 */
void SI_SetMainWid::updateSlot(int addr)
{
    for(int i=0; i<4; ++i) {
        mThresholdSetWid[i]->init(SI_SetMode_Vol+i, mData->data);
    }

    int line = mData->data.lineNum;
    uint *ele = mData->data.ele;
    int br = mData->data.br;
    mEleSetWid->updateData(addr, line, ele, br);
}
