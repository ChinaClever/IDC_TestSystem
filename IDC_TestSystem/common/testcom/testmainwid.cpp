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
    mDevType = 0;
    QTimer::singleShot(400,this,SLOT(initFunSLot()));
}

TestMainWid::~TestMainWid()
{
    delete ui;
}


void TestMainWid::initFunSLot()
{
    mSerialNumDlg = new TestSerialNumDlg(this);
    mSerialNumDlg->init(mConfig, mDevType);

    mResultWid = new TestResultWid(ui->stackedWid);
    ui->stackedWid->addWidget(mResultWid);
    mResultWid->init(mConfig->item);

    mItemTableWid = new TestItemTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mItemTableWid);
    mItemTableWid->initPackets(mPackets);

    mDataTableWid = new TestDataTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mDataTableWid);
    mDataTableWid->initPackets(mPackets);
    mDataTableWid->init(mConfig->item);

    mDataSave = new TestDataSave(this);
    mDataSave->init(mConfig->item);
}


void TestMainWid::startTest()
{
    int ret = mSerialNumDlg->exec();
    if( ret == QDialog::Accepted ) {

        mItemTableWid->startSlot();
        mResultWid->startSlot();
        mDataTableWid->startSLot();
    }

}

void TestMainWid::pauseTest()
{

}

void TestMainWid::continueTest()
{

}

void TestMainWid::overTest()
{


    mResultWid->resultSlot();
    mDataSave->saveTestData();
}


void TestMainWid:: updateWidSlot(int id)
{
    ComTableWid *wid = nullptr;
    switch (id) {
    case Test_Start: startTest(); break;
    case Test_Pause: pauseTest(); break;
    case Test_Continue: continueTest(); break;
    case Test_Over: overTest(); break;

    case Test_Items_Wid: wid = mItemTableWid; break;
    case Test_Datas_Wid: wid = mDataTableWid; break;
    case Test_Result_Wid:  ui->stackedWid->setCurrentWidget(mResultWid); break;
    default:  break;
    }
    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
