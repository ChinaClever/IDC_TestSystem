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
    mConfig = nullptr;
    QTimer::singleShot(2600,this,SLOT(initFunSLot()));
}

TestMainWid::~TestMainWid()
{
    delete ui;
}


void TestMainWid::initFunSLot()
{
    if(!mConfig) { QTimer::singleShot(1000,this,SLOT(initFunSLot())); return;}
    mSerialNumDlg = new TestSerialNumDlg(this);
    mSerialNumDlg->init(mConfig);

    mResultWid = new TestResultWid(ui->stackedWid);
    mResultWid->init(mConfig->item);
    ui->stackedWid->addWidget(mResultWid);

    mItemTableWid = new TestItemTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mItemTableWid);
    mItemTableWid->initPackets(mPackets);
    mItemTableWid->init(mConfig->item);

    mDataTableWid = new TestDataTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mDataTableWid);
    mDataTableWid->initPackets(mPackets);
    mDataTableWid->init(mConfig->item);

    mCoreThread->init(mConfig->item, mPackets, mTrans);
    connect(mCoreThread, SIGNAL(overSig()), this, SLOT(overSlot()));
    connect(mItemTableWid,SIGNAL(allNumsSig(int)),mCoreThread,SLOT(allNumsSlot(int)));

    mDataSave = new TestDataSave(this);
    mDataSave->init(mConfig->item);

    mWebSocket = new TestWebSocket(this);
    mWebSocket->init(mConfig->item);
}


void TestMainWid::startTest()
{
    int ret = mSerialNumDlg->exec();
    if( ret == QDialog::Accepted ) {
        mConfig->item->mode = Test_Start;
        mTrans->clearSnmpCmd();//把上一次的snmp命令清除
        mCoreThread->startThread();
        mItemTableWid->startSlot();
        mResultWid->startSlot();
        mDataTableWid->startSLot();        
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

void TestMainWid::overSlot()
{
    if(mConfig->item->mode != Test_Over)//避免重复点击结束按钮
    {
        mConfig->item->mode = Test_Over;
        mTrans->stopUpdateData();
        mResultWid->resultSlot();
        mDataSave->saveTestData();
        mWebSocket->saveTestData();
        mSerialNumDlg->getSerialNum();
    }
}

void TestMainWid::overTest()
{
    QuMsgBox box(this, tr("是否停止测试?"));
    if(box.Exec()){
        overSlot();
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
