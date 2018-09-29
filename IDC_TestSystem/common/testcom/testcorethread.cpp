#include "testcorethread.h"

TestCoreThread::TestCoreThread(QObject *parent) : QThread(parent)
{
    mTrans = nullptr;
}


void TestCoreThread::startThread()
{
    mItemId = 1;
    mDevPacket = &(mPackets->dev[mItem->devId]);
}


void TestCoreThread::stopThread()
{
    quit();
    terminate();
//    wait();
}

void TestCoreThread::conditionExec(bool s)
{
    if(mItem->mode == Test_Pause) {
        do{
            msleep(1);
        } while(mItem->mode == Test_Pause);
    }

    if(mItem->mode == Test_Over){
        stopThread();
    }

    if(mItem->serialNum.errStop) {
        if(!s) stopThread();
    }
}

bool TestCoreThread::appendResult(sTestDataItem &item)
{
    QString str = tr("失败");
    if(item.status) {
        str = tr("成功");
    }
    item.id = mItemId++;
    item.result = str;
    mItem->dataItem.append(item);
    conditionExec(item.status);

    return item.status;
}

bool TestCoreThread::snmpTrans()
{
    bool ret = false;
    sTestDataItem item;

    item.item = tr("通讯检查");
    item.subItem = tr("SNMP通讯测试");
    item.expect = tr("通过SNMP能获取到设备数据");

    QString str = tr("SNMP通讯失败");
    mTrans->snmpUpdateData(); sleep(5);
    if(mDevPacket->offLine) {
        ret = true;
        str = tr("SNMP通讯成功");
    }

    item.status = ret;
    item.measured = str;
    mTrans->snmpStop();

    return appendResult(item);
}

bool TestCoreThread::rtuTrans()
{
    bool ret = false;
    sTestDataItem item;

    item.item = tr("通讯检查");
    item.subItem = tr("Modbus通讯测试");
    item.expect = tr("通过Modbus能获取到设备数据");

    QString str = tr("Modbus通讯失败");
    mTrans->rtuUpdateData(); sleep(5);
    if(mDevPacket->offLine) {
        ret = true;
        str = tr("Modbus通讯成功");
    }

    item.status = ret;
    item.measured = str;
    mTrans->rtuStop();

    return appendResult(item);
}

bool TestCoreThread::transmission()
{
    bool ret = rtuTrans();
    if(mItem->isSnmp)
        ret = snmpTrans();

    return ret;
}

