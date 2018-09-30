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
    QTimer::singleShot(400,this,SLOT(initFunSLot()));
}

TestMainWid::~TestMainWid()
{
    delete ui;
}


void TestMainWid::initFunSLot()
{
    mSerialNumDlg = new TestSerialNumDlg(this);
    mSerialNumDlg->init(mConfig);

    mResultWid = new TestResultWid(ui->stackedWid);
    ui->stackedWid->addWidget(mResultWid);
    mResultWid->init(mConfig->item);

    mItemTableWid = new TestItemTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mItemTableWid);
    mItemTableWid->initPackets(mPackets);
    mItemTableWid->init(mConfig->item);

    mDataTableWid = new TestDataTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mDataTableWid);
    mDataTableWid->initPackets(mPackets);
    mDataTableWid->init(mConfig->item);

    mCoreThread->init(mConfig->item, mPackets, mTrans);
    mDataSave = new TestDataSave(this);
    mDataSave->init(mConfig->item);
}


void TestMainWid::startTest()
{
    int ret = mSerialNumDlg->exec();
    if( ret == QDialog::Accepted ) {

        mConfig->item->mode = Test_Start;
        mItemTableWid->startSlot();
        mResultWid->startSlot();
        mDataTableWid->startSLot();
        mCoreThread->startThread();
    }

}

void TestMainWid::pauseTest()
{
    mConfig->item->mode = Test_Pause;
}

void TestMainWid::continueTest()
{
    mConfig->item->mode = Test_Start;
}

void TestMainWid::overTest()
{
    QuMsgBox box(this, tr("是否停止??"));
    if(box.Exec()){
        mResultWid->resultSlot();
        mDataSave->saveTestData();
        mConfig->item->mode = Test_Over;
    }
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
