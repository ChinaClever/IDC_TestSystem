/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "testmainwid.h"
#include "ui_testmainwid.h"

TestMainWid::TestMainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestMainWid)
{
    ui->setupUi(this);

    QTimer::singleShot(600,this,SLOT(initFunSLot()));
}

TestMainWid::~TestMainWid()
{
    delete ui;
}


void TestMainWid::initFunSLot()
{
    mResultWid = new TestResultWid(ui->stackedWid);
    ui->stackedWid->addWidget(mResultWid);

    mItemTableWid = new TestItemTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mItemTableWid);

    mDataTableWid = new TestDataTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mDataTableWid);
}


void TestMainWid:: updateWidSlot(int id)
{
    ComTableWid *wid = nullptr;
    switch (id) {
    case Test_Items_Wid: wid = mItemTableWid; break;
    case Test_Datas_Wid: wid = mDataTableWid; break;
    case Test_Result_Wid:  ui->stackedWid->setCurrentWidget(mResultWid); break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
