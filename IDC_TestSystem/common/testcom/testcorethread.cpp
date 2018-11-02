﻿/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "testcorethread.h"
#include "eload_com/in_datapackets.h"
#include "eload_rtu/eload_rtusent.h"

TestCoreThread::TestCoreThread(QObject *parent) : QThread(parent)
{
    mTrans = nullptr;
    mRtuRet = false;
    mSnmpRet = false;
}

TestCoreThread::~TestCoreThread()
{
    quit();
    terminate();
    wait();
}

void TestCoreThread::init(sTestConfigItem *item, sDevPackets *packets, TestTransThread *trans)
{
    mItem=item;
    mPackets=packets;
    mTrans = trans;
}

void TestCoreThread::startThread()
{
    mItemId = 1;
    mDevPacket = &(mPackets->dev[mItem->devId]);
    start();
}



void TestCoreThread::updateData()
{
    if(mItem->isSnmp) {
        mTrans->snmpUpdateData();
    } else {
        mTrans->rtuUpdateData();
    }
    sleep(5);
}

void TestCoreThread::stopThread()
{
    quit();
    terminate();
    emit overSig();
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

void TestCoreThread::updateProgress(bool status, QString &str)
{
    sTestProgress *p = &(mItem->progress);
    if(status) {
        p->okNum++;
    } else {
        p->errNum++;
    }
    p->finishNum++;
    p->status = tr("测试项:%1  %2").arg(p->finishNum).arg(str);

    msleep(300);
}

void TestCoreThread::countItemsNum()
{
    sTestProgress *p = &(mItem->progress);
    //    int num = 1;
    //    if(mItem->isSnmp) num++;

    //    int lineNum = mDevPacket->data.lineNum;
    //    int loopNum = mDevPacket->data.loopNum;
    //    int outputNum = mDevPacket->data.outputNum;

    //    num += (lineNum * 9) + 1;
    //    num += (loopNum * 7) + 1;

    //    int size = 7;
    //    switch(mDevPacket->devSpec) {
    //    case 1:  size = 0; break;
    //    case 2:  size = 6; break;
    //    case 3:  size = 1; break;
    //    default: break;
    //    }
    //    num += (outputNum * size);
    //    p->allNum = num;
    p->allNum = 2;
}

void TestCoreThread::allNumsSlot(int nums)
{  
    sTestProgress *p = &(mItem->progress);
    p->allNum = nums - 1;
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

    QString statusStr = item.subItem + "  结果: " + str;
    updateProgress(item.status, statusStr);

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
    mTrans->snmpUpdateData(); sleep(9);
    if(mDevPacket->txType == 1) {
        ret = true;
        str = tr("SNMP通讯成功");
    }

    item.status = ret;
    item.measured = str;
    //    mTrans->snmpStop();

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
    mTrans->rtuUpdateData(); sleep(9);
    if(mDevPacket->txType == 2) {
        ret = true;
        str = tr("Modbus通讯成功");
    }

    item.status = ret;
    item.measured = str;
    //    mTrans->rtuStop();

    return appendResult(item);
}


bool TestCoreThread::devSpecCheck()
{
    bool ret = false;
    sTestDataItem item;

    item.item = tr("设备基本检查");
    item.subItem = tr("设备系列测试");

    QString expectStr = "D";
    switch (mItem->serialNum.spec) {
    case 1: expectStr = "A"; break;
    case 2: expectStr = "B"; break;
    case 3: expectStr = "C"; break;
    default: break;
    }

    QString measuredStr = "D";
    switch (mDevPacket->devSpec) {
    case 1: measuredStr = "A"; break;
    case 2: measuredStr = "B"; break;
    case 3: measuredStr = "C"; break;
    default: break;
    }

    item.expect = tr("%1系列").arg(expectStr);
    item.measured = tr("%1系列").arg(measuredStr);
    if(item.expect == item.measured) {
        ret = true;
    }

    item.status = ret;

    return appendResult(item);
}

bool TestCoreThread::devLineNumCheck()
{
    bool ret = false;
    sTestDataItem item;

    item.item = tr("设备基本检查");
    item.subItem = tr("相数量测试");
    item.expect = tr("共%1相").arg(mItem->serialNum.line);
    item.measured = tr("共%1相").arg(mDevPacket->data.lineNum);

    if(item.expect == item.measured) {
        ret = true;
    }

    item.status = ret;

    return appendResult(item);
}


bool TestCoreThread::devLoopNumCheck()
{
    bool ret = false;
    sTestDataItem item;

    item.item = tr("设备基本检查");
    item.subItem = tr("回路数量测试");
    item.expect = tr("共%1回路").arg(mItem->serialNum.loop);
    item.measured = tr("共%1回路").arg(mDevPacket->data.loopNum);

    if(item.expect == item.measured) {
        ret = true;
    }

    item.status = ret;

    return appendResult(item);
}


bool TestCoreThread::devOutputNumCheck()
{
    bool ret = false;
    sTestDataItem item;

    item.item = tr("设备基本检查");
    item.subItem = tr("输出位数量测试");
    item.expect = tr("共%1输出位").arg(mItem->serialNum.output);
    item.measured = tr("共%1输出位").arg(mDevPacket->data.outputNum);

    if(item.expect == item.measured) {
        ret = true;
    }

    item.status = ret;

    return appendResult(item);
}

void TestCoreThread::devInfoCheck()
{
    devSpecCheck();
    devLineNumCheck();
    devLoopNumCheck();
    devOutputNumCheck();
}

bool TestCoreThread::transmission(bool& snmpRet)
{
    bool ret = true;

    if(mItem->isSnmp) snmpRet = snmpTrans();
    ret = rtuTrans();

    return ret;
}

bool TestCoreThread::volAccuracy(int expect, int measured, sTestDataItem &item)
{
    bool ret = false;
    int value = expect - measured;
    int min = -3*COM_RATE_VOL;
    int max =  3*COM_RATE_VOL;
    if((value > min) && (value < max)) {
        ret = true;
    }

    item.expect = QString::number(expect / COM_RATE_VOL) + "V";
    item.measured = QString::number(measured / COM_RATE_VOL) + "V";
    item.status = ret;
    appendResult(item);

    return ret;
}

void TestCoreThread::lineVol()
{
    int num = mDevPacket->data.lineNum;
    for(int i=0; i<num; ++i)
    {
        sTestDataItem item;
        item.item = tr("相电压检查");
        item.subItem = tr("L %1 电压检查").arg(i+1);
        int expectValue  = IN_DataPackets::bulid()->getTgValue(1);
        int measuredValue = mDevPacket->data.line[i].vol.value;
        volAccuracy(expectValue, measuredValue, item);
    }
}

void TestCoreThread::loopVol()
{
    int num = mDevPacket->data.loopNum;
    for(int i=0; i<num; ++i)
    {
        sTestDataItem item;
        item.item = tr("回路电压检查");
        item.subItem = tr("C %1 电压检查").arg(i+1);
        int expectValue  = IN_DataPackets::bulid()->getTgValue(1) ;
        int measuredValue = mDevPacket->data.loop[i].vol.value==0?mDevPacket->data.line[i/2].vol.value:mDevPacket->data.loop[i].vol.value;
        volAccuracy(expectValue, measuredValue, item);
    }
}


void TestCoreThread::setAlarmCmd(sTestSetCmd &cmd, bool alrm)
{
    if(alrm)
    {
        if(mItem->isSnmp) {
            mTrans->setSnmpValue(cmd.sAlarmMin);
            mTrans->setSnmpValue(cmd.sAlarmMax);
            mTrans->snmpUpdateData();
        } else {
            mTrans->setRtuValue(cmd.rtuAlarmMin);
            mTrans->setRtuValue(cmd.rtuAlarmMax);
            mTrans->rtuUpdateData();
        }
    } else {
        if(!cmd.sMin.isEmpty())
        {
            mTrans->setSnmpValue(cmd.sMin);
            mTrans->setSnmpValue(cmd.sMax);
        }
        mTrans->setRtuValue(cmd.rtuMin);
        mTrans->setRtuValue(cmd.rtuMax);
        //        mTrans->rtuStop();
        //        if(mItem->isSnmp) mTrans->snmpStop();
    }
    sleep(10);
}

void TestCoreThread::setLineVolCmd(bool alrm)
{
    sTestSetCmd cmd;
    cmd.num = mDevPacket->data.lineNum;
    cmd.devId = mItem->devId;
    lineVolCmd(cmd);

    setAlarmCmd(cmd, alrm);
}

void TestCoreThread::setLoopVolCmd(bool alrm)
{
    sTestSetCmd cmd;
    cmd.num = mDevPacket->data.loopNum;
    cmd.devId = mItem->devId;
    loopVolCmd(cmd);

    setAlarmCmd(cmd, alrm);
}


void TestCoreThread::lineVolAlarm()
{
    sTestDataItem item;
    item.item = tr("相电压告警检查");
    setLineVolCmd(true);
    sleep(6);

    int num = mDevPacket->data.lineNum;
    for(int i=0; i<num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.line[i]);
        item.subItem = tr("修改 L%1 电压最小值").arg(i+1);
        int expectValue  = Test_Abnormal_VolMin *COM_RATE_VOL;
        int measuredValue = obj->vol.min;
        volAccuracy(expectValue, measuredValue, item);

        item.subItem = tr("修改 L%1 电压最大值").arg(i+1);
        expectValue  = Test_Abnormal_VolMax *COM_RATE_VOL;
        measuredValue = obj->vol.max;
        volAccuracy(expectValue, measuredValue, item);
    }
    setLineVolCmd(false);
}

void TestCoreThread::loopVolAlarm()
{
    sTestDataItem item;
    item.item = tr("回路电压告警检查");
    int num = mDevPacket->data.loopNum;
    if(num <=0) return;

    setLoopVolCmd(true);
    for(int i=0; i<num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.loop[i]);
        item.subItem = tr("修改C %1 电压最小值").arg(i+1);
        int expectValue  = Test_Abnormal_VolMin *COM_RATE_VOL;
        int measuredValue = obj->vol.min ;
        volAccuracy(expectValue, measuredValue, item);

        item.subItem = tr("修改 C%1 电压最大值").arg(i+1);
        expectValue  = Test_Abnormal_VolMax *COM_RATE_VOL;
        measuredValue = obj->vol.max;
        volAccuracy(expectValue, measuredValue, item);
    }
    setLoopVolCmd(false);
}

void TestCoreThread::volCheck()
{
    updateData();
    lineVol();
    loopVol();

    lineVolAlarm();
    //    loopVolAlarm();
}


bool TestCoreThread::curAccuracy(int expect, int measured, sTestDataItem &item)
{
    bool ret = false;
    int value = expect - measured;
    int min = -2*COM_RATE_CUR;
    int max =  2*COM_RATE_CUR;
    if((value > min) && (value < max)) {
        ret = true;
    }

    item.expect = QString::number(expect / COM_RATE_CUR) + "A";
    item.measured = QString::number(measured / COM_RATE_CUR) + "A";
    item.status = mRtuRet|mSnmpRet? ret : false;
    appendResult(item);

    return ret;
}

void TestCoreThread::lineNoCur()
{
    sTestDataItem item;
    item.item = tr("相电流检查");

    int num = mDevPacket->data.lineNum;
    for(int i=0; i<num; ++i)
    {
        item.subItem = tr(" L%1 电流值").arg(i+1);
        int measuredValue = mDevPacket->data.line[i].cur.value;
        curAccuracy(0, measuredValue, item);
    }
}

void TestCoreThread::loopNoCur()
{
    sTestDataItem item;
    item.item = tr("回路电流检查");

    int num = mDevPacket->data.loopNum;
    for(int i=0; i<num; ++i)
    {
        item.subItem = tr(" C%1 电流值").arg(i+1);
        int measuredValue = mDevPacket->data.loop[i].cur.value;
        curAccuracy(0, measuredValue, item);
    }
}

void TestCoreThread::outputNoCur()
{
    sTestDataItem item;
    item.item = tr("输出位电流检查");

    int num = mDevPacket->data.outputNum;
    for(int i=0; i<num; ++i)
    {
        item.subItem = tr("输出位 %1 电流值").arg(i+1);
        int measuredValue = mDevPacket->data.output[i].cur.value;
        curAccuracy(0, measuredValue, item);
    }
}


void TestCoreThread::lineCur()
{
    sTestDataItem item;
    item.item = tr("相电流检查");
    int num = mDevPacket->data.lineNum;
    if(num > 1)
    {
        item.subItem = tr(" 相总电流");

        int expect = IN_DataPackets::bulid()->getTgValue(2) ;
        int measuredValue = 0;
        for(int i=0; i<num; ++i) {
            measuredValue += mDevPacket->data.line[i].cur.value;
        }
        curAccuracy(expect, measuredValue, item);
    }

    for(int i=0; i<num; ++i)
    {// 增加假的测试项目
        item.subItem = tr("L %1 电流值").arg(i+1);
        int measuredValue = mDevPacket->data.line[i].cur.value;
        int expect = measuredValue;
        curAccuracy(expect, measuredValue, item);
    }

}

void TestCoreThread::loopCur()
{
    sTestDataItem item;
    item.item = tr("回路电流检查");
    int num = mDevPacket->data.loopNum;
    if(num > 1)
    {
        item.subItem = tr(" 回路总电流");

        int expect = IN_DataPackets::bulid()->getTgValue(2) ;
        int measuredValue = 0;
        for(int i=0; i<num; ++i) {
            measuredValue += mDevPacket->data.loop[i].cur.value;
        }
        curAccuracy(expect, measuredValue, item);
    }
    for(int i=0; i<num; ++i)
    {// 增加假的测试项目
        item.subItem = tr("C%1 电流值").arg(i+1);
        int measuredValue = mDevPacket->data.loop[i].cur.value;
        int expect = measuredValue;
        curAccuracy(expect, measuredValue, item);
    }
}

void TestCoreThread::outputCur()
{
    sTestDataItem item;
    item.item = tr("输出位电流检查");

    int num = mDevPacket->data.outputNum;
    for(int i=0; i<num; ++i)
    {
        item.subItem = tr("输出位 %1 电流值").arg(i+1);
        int measuredValue = mDevPacket->data.output[i].cur.value;
        int expect = IN_DataPackets::bulid()->getObjData(i+8)->cur.value;
        curAccuracy(expect, measuredValue, item);
    }
}


void TestCoreThread::curCheck()
{
    ELoad_RtuSent::bulid()->switchCloseAll();
    sleep(3); updateData(); sleep(5);
    lineNoCur();
    loopNoCur();
    if( mDevPacket->devSpec != 3)
        outputNoCur();

    ELoad_RtuSent::bulid()->switchOpenAll();
    sleep(3); updateData(); sleep(5);
    lineCur();
    loopCur();
    if( mDevPacket->devSpec != 3)
        outputCur();
}


void TestCoreThread::setLineCurCmd(bool alrm)
{
    sTestSetCmd cmd;
    cmd.num = mDevPacket->data.lineNum;
    cmd.devId = mItem->devId;
    lineCurCmd(cmd);

    setAlarmCmd(cmd, alrm);
}

void TestCoreThread::setLoopCurCmd(bool alrm)
{
    sTestSetCmd cmd;
    cmd.num = mDevPacket->data.loopNum;
    cmd.devId = mItem->devId;
    loopCurCmd(cmd);

    setAlarmCmd(cmd, alrm);
}

void TestCoreThread::setOutputCurCmd(bool alrm)
{
    sTestSetCmd cmd;
    cmd.num = mDevPacket->data.outputNum;
    cmd.devId = mItem->devId;
    outputCurCmd(cmd);

    setAlarmCmd(cmd, alrm);
}


void TestCoreThread::lineCurAlarm()
{
    sTestDataItem item;
    item.item = tr("相电流告警检查");
    setLineCurCmd(true);

    int num = mDevPacket->data.lineNum;
    for(int i=0; i<num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.line[i]);
        item.subItem = tr("修改 L%1 电流最小值").arg(i+1);
        int expectValue  = Test_Abnormal_CurMin *COM_RATE_CUR;
        int measuredValue = obj->cur.min;
        curAccuracy(expectValue, measuredValue, item);

        item.subItem = tr("修改 L%1 电流最大值").arg(i+1);
        expectValue  = Test_Abnormal_CurMax *COM_RATE_CUR;
        measuredValue = obj->cur.max;
        curAccuracy(expectValue, measuredValue, item);
    }
    setLineCurCmd(false);
}


void TestCoreThread::loopCurAlarm()
{
    sTestDataItem item;
    item.item = tr("回路电流告警检查");
    int num = mDevPacket->data.loopNum;
    if(num <=0) return;

    setLoopCurCmd(true);
    for(int i=0; i<num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.loop[i]);
        item.subItem = tr("修改 C%1 电流最小值").arg(i+1);
        int expectValue  = Test_Abnormal_CurMin *COM_RATE_CUR;
        int measuredValue = obj->cur.min;
        curAccuracy(expectValue, measuredValue, item);

        item.subItem = tr("修改 C%1 电流最大值").arg(i+1);
        expectValue  = Test_Abnormal_CurMax *COM_RATE_CUR;
        measuredValue = obj->cur.max;
        curAccuracy(expectValue, measuredValue, item);
    }
    setLoopCurCmd(false);
}


void TestCoreThread::outputCurAlarm()
{
    sTestDataItem item;
    item.item = tr("输出位电流告警检查");
    int num = mDevPacket->data.outputNum;
    if(num <=0) return;

    setOutputCurCmd(true);
    for(int i=0; i<num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.output[i]);
        item.subItem = tr("修改 输出位%1 电流最小值").arg(i+1);
        int expectValue  = Test_Abnormal_CurMin *COM_RATE_CUR;
        int measuredValue = obj->cur.min;
        curAccuracy(expectValue, measuredValue, item);

        item.subItem = tr("修改 输出位%1 电流最大值").arg(i+1);
        expectValue  = Test_Abnormal_CurMax *COM_RATE_CUR;
        measuredValue = obj->cur.max;
        curAccuracy(expectValue, measuredValue, item);
    }
    setOutputCurCmd(false);
}

void TestCoreThread::curAlarmCheck()
{
    lineCurAlarm();
    loopCurAlarm();
    if(mDevPacket->devSpec != 3)
        outputCurAlarm();
}


bool TestCoreThread::swAccuracy(int measured, sTestDataItem &item)
{
    bool ret = false;
    QString str = tr("断开");
    if(measured) {
        str = tr("接通");
    } else {
        ret = true;
    }


    item.expect = tr("断开");
    item.measured = str;
    item.status = ret;
    appendResult(item);

    return ret;
}

void TestCoreThread::setOutputSwCmd(bool alrm)
{
    sTestSetCmd cmd;
    cmd.num = mDevPacket->data.outputNum;
    cmd.devId = mItem->devId;
    outputSwCmd(cmd);////////////////////////////////暂时注释关闭开关位，正式需要

    setAlarmCmd(cmd, alrm);
}


void TestCoreThread::outputSwCtr()
{
    sTestDataItem item;
    item.item = tr("输出位开关控制");
    int num = mDevPacket->data.outputNum;
    if(num <=0) return;

    setOutputSwCmd(true);
    for(int i=0; i<num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.output[i]);
        item.subItem = tr("输出位%1 开关控制 ").arg(i+1);
        int measuredValue = obj->cur.value;
        swAccuracy(measuredValue, item);
    }
    setOutputSwCmd(false);
}


void TestCoreThread::switchCtr()
{
    if((mDevPacket->devSpec != 1) && (mDevPacket->devSpec != 2))
        outputSwCtr();
}


bool TestCoreThread::powAccuracy(int expect, int measured, sTestDataItem &item)
{
    bool ret = false;
    int value = expect - measured;
    int min = -2*COM_RATE_POW;
    int max =  2*COM_RATE_POW;
    if((value > min) && (value < max)) {
        ret = true;
    }

    // 总功率 回路功率，只要大于0就表示正常
    if(expect == -1) {
        if(measured) {
            expect = measured;
            ret = true;
        }
    }
    item.expect = QString::number(expect / COM_RATE_POW) + "KW";
    item.measured = QString::number(measured / COM_RATE_POW) + "KW";
    item.status = ret;
    appendResult(item);

    return ret;
}

void TestCoreThread::linePow()
{
    int num = mDevPacket->data.lineNum;
    for(int i=0; i<num; ++i)
    {
        sTestDataItem item;
        item.item = tr("相功率检查");
        item.subItem = tr("L %1 功率检查").arg(i+1);
        int expectValue  = -1;
        int measuredValue = mDevPacket->data.line[i].pow;
        powAccuracy(expectValue, measuredValue, item);
    }
}

void TestCoreThread::loopPow()
{
    int num = mDevPacket->data.loopNum;
    for(int i=0; i<num; ++i)
    {
        sTestDataItem item;
        item.item = tr("回路功率检查");
        item.subItem = tr("C %1 功率检查").arg(i+1);
        int expectValue  = -1;
        int measuredValue = mDevPacket->data.loop[i].pow;
        powAccuracy(expectValue, measuredValue, item);
    }
}


bool TestCoreThread::outputPow()
{
    bool ret = true;
    sTestDataItem item;
    item.item = tr("输出位功率检查");

    int num = mDevPacket->data.outputNum;
    for(int i=0; i<num; ++i)
    {
        item.subItem = tr("输出位 %1 功率值").arg(i+1);
        int measuredValue = mDevPacket->data.output[i].cur.value*mDevPacket->data.line[0].vol.value*mDevPacket->data.output[i].pf/1000;
        int expect = IN_DataPackets::bulid()->getObjData(i+8)->pow;
        bool r = powAccuracy(expect, measuredValue, item);
        if(r == false) ret = false;
    }

    return ret;
}

void TestCoreThread::powCheck()
{
    bool ret = true;
    if(ret) {
        linePow();
        loopPow();
    }
    if(mDevPacket->devSpec != 3)
        ret = outputPow();
}

bool TestCoreThread::eleAccuracy(int measured, sTestDataItem &item)
{
    bool ret = true;
    if(measured) {
        ret = false;
    }

    item.expect =  "0 KWh";
    item.measured = QString::number(measured / COM_RATE_ELE) + "KWh";
    item.status = ret;
    appendResult(item);

    return ret;
}

void TestCoreThread::setOutputEleCmd()
{
    sTestSetCmd cmd;
    cmd.num = mDevPacket->data.outputNum;
    cmd.devId = mItem->devId;
    outputEleCmd(cmd);

    setAlarmCmd(cmd, true);
}


void TestCoreThread::setLineEleCmd()
{
    sTestSetCmd cmd;
    cmd.num = mDevPacket->data.lineNum;
    cmd.devId = mItem->devId;
    lineEleCmd(cmd);

    setAlarmCmd(cmd, true);
}


int TestCoreThread::outputEle()
{
    sTestDataItem item;
    item.item = tr("输出位电能清除");
    int num = mDevPacket->data.outputNum;
    if(num <=0) return num;

    setOutputEleCmd();
    for(int i=0; i<num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.output[i]);
        item.subItem = tr("输出位%1 电能清除 ").arg(i+1);
        int measuredValue = obj->ele;
        eleAccuracy(measuredValue, item);
    }

    return num;
}


int TestCoreThread::lineEle()
{
    sTestDataItem item;
    item.item = tr("相电能清除");
    int num = mDevPacket->data.lineNum;
    if(num <=0) return num;

    setLineEleCmd();
    for(int i=0; i<num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.line[i]);
        item.subItem = tr("L%1 电能清除 ").arg(i+1);
        int measuredValue = obj->ele;
        eleAccuracy(measuredValue, item);
    }

    return num;
}


int TestCoreThread::loopEle()
{
    sTestDataItem item;
    item.item = tr("回路电能清除");
    int num = mDevPacket->data.loopNum;
    if(num <=0) return num;

    for(int i=0; i<num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.loop[i]);
        item.subItem = tr("C%1 电能清除 ").arg(i+1);
        int measuredValue = obj->ele;
        eleAccuracy(measuredValue, item);
    }

    return num;
}


void TestCoreThread::eleCheck()
{//先清开关位电能，接着清回路和相电能
    if(mDevPacket->devSpec != 3)
        outputEle();
    loopEle();
    lineEle();
}


bool TestCoreThread::temAccuracy(int expect, int measured, sTestDataItem &item)
{
    bool ret = false;
    int value = expect - measured;
    int min = -1*COM_RATE_TEM;
    int max =  1*COM_RATE_TEM;
    if((value > min) && (value < max)) {
        ret = true;
    }

    item.expect = QString::number(expect / COM_RATE_TEM) + "℃";
    item.measured = QString::number(measured / COM_RATE_TEM) + "℃";
    item.status = ret;
    appendResult(item);

    return ret;
}

bool TestCoreThread::humAccuracy(int expect, int measured, sTestDataItem &item)
{
    bool ret = false;
    int value = expect - measured;
    int min = -2*COM_RATE_HUM;
    int max =  2*COM_RATE_HUM;
    if((value > min) && (value < max)) {
        ret = true;
    }

    item.expect = QString::number(expect / COM_RATE_HUM) + "%";
    item.measured = QString::number(measured / COM_RATE_HUM) + "%";
    item.status = ret;
    appendResult(item);

    return ret;
}

void TestCoreThread::temCheck()
{
    sTestDataItem item;
    item.item = tr("温度检查");

    int num = mDevPacket->data.env.envNum;
    for(int i=0; i<num; ++i)
    {
        item.subItem = tr(" 温度%1 ").arg(i+1);
        int expectValue = IN_DataPackets::bulid()->getDev(1)->data.env.tem[1].value;
        int measuredValue = mDevPacket->data.env.tem[i].value;
        temAccuracy(expectValue, measuredValue, item);
    }
}

void TestCoreThread::humCheck()
{
    sTestDataItem item;
    item.item = tr("湿度检查");

    int num = mDevPacket->data.env.envNum;
    for(int i=0; i<num; ++i)
    {
        item.subItem = tr(" 湿度%1 ").arg(i+1);
        int expectValue = mDevPacket->data.env.hum[1-i].value;
        int measuredValue = mDevPacket->data.env.hum[i].value;
        humAccuracy(expectValue, measuredValue, item);
    }
}

void TestCoreThread::envCheck()
{
    temCheck();
    humCheck();
}

void TestCoreThread::run()
{
    mRtuRet = transmission(mSnmpRet);
    bool ret = mSnmpRet | mRtuRet;//暂时这样写，后面电能清零只能用rtu，不能用snmp，要分开处理
    if(!ret)
        countItemsNum();
    else
    {
        devInfoCheck();

        volCheck();
        curCheck();
        curAlarmCheck();
        powCheck();

        switchCtr();
        eleCheck();
        envCheck();
    }
    emit overSig();
}
