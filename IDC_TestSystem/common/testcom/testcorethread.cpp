/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "testcorethread.h"
#include "eload_com/in_datapackets.h"
#include "eload_rtu/eload_rtusent.h"
#include "eload_home/eload_inputhomewid.h"

TestCoreThread::TestCoreThread(QObject *parent) : QThread(parent)
{
    mTrans = nullptr;
}

TestCoreThread::~TestCoreThread()
{
    quit();
    terminate();
    wait();
}

void TestCoreThread::init(sTestConfigItem *item, sDevPackets *packets, TestTransThread *trans)
{
    mItem = item;
    mPackets = packets;
    mTrans = trans;
}

void TestCoreThread::startThread()
{
    mItemId = 1;
    mDevPacket = &(mPackets->dev[mItem->devId]);
    mDevPacket->data.lineNum = 0;
    mDevPacket->data.loopNum = 0;
    mDevPacket->data.outputNum = 0;
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
    emit overSig();
    QThread::exit(0);
    quit();
    terminate();
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
    mTrans->snmpUpdateData();
    snmpTransDelay();

    if(mDevPacket->txType == 1) {
        ret = true;
        str = tr("SNMP通讯成功");
    }

    item.status = ret;
    item.measured = str;
    // mTrans->snmpStop();

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
    mTrans->rtuUpdateData();
    rtuTransDelay();//rpdu23 zpdu20 必须延长时间，不然读不到modbus标志位以及后面修改阈值也读不到值
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

int TestCoreThread::getLineNum()
{
    return mDevPacket->data.lineNum;
}

bool TestCoreThread::devLineNumCheck()
{
    bool ret = false;
    sTestDataItem item;

    item.item = tr("设备基本检查");
    item.subItem = tr("相数量测试");
    item.expect = tr("共%1相").arg(mItem->serialNum.line);
    item.measured = tr("共%1相").arg(getLineNum());

    if(item.expect == item.measured) {
        ret = true;
    }

    item.status = ret;

    return appendResult(item);
}

int TestCoreThread::getLoopNum()
{
    return mDevPacket->data.loopNum;
}

bool TestCoreThread::devLoopNumCheck()
{
    bool ret = false;
    sTestDataItem item;

    item.item = tr("设备基本检查");
    item.subItem = tr("回路数量测试");
    item.expect = tr("共%1回路").arg(mItem->serialNum.loop);
    item.measured = tr("共%1回路").arg(getLoopNum());
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

bool TestCoreThread::transmission()
{
    bool ret=true, snmpRet=true;

    if(mItem->isSnmp)  snmpRet = snmpTrans();
    ret = rtuTrans();

    if(mItem->serialNum.name == "SI-PDU")  snmpRet = true;

    return ret && snmpRet;
}

bool TestCoreThread::volAccuracy(int expect, int measured, sTestDataItem &item)
{
    bool ret = false;
    int value = expect - measured;
    int min = -3*COM_RATE_VOL;
    int max =  3*COM_RATE_VOL;
    if((value >= min) && (value <= max)) {
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
    for(int i = 0; i < num; ++i)
    {
        sTestDataItem item;
        item.item = tr("相电压检查");
        item.subItem = tr(" L%1 电压检查").arg(i+1);
        int expectValue  = IN_DataPackets::bulid()->getTgValueByIndex(1,i+1);
        int measuredValue = mDevPacket->data.line[i].vol.value;
        volAccuracy(expectValue, measuredValue, item);
    }
}

void TestCoreThread::loopVol()
{
    int num = mDevPacket->data.loopNum;
    for(int i = 0; i < num; ++i)
    {
        sTestDataItem item;
        item.item = tr("回路电压检查");
        item.subItem = tr(" C%1 电压检查").arg(i+1);
        int expectValue  = IN_DataPackets::bulid()->getTgValueByIndex(1,i/2+1);
        int measuredValue = mDevPacket->data.loop[i].vol.value==0?mDevPacket->data.line[i/2].vol.value:mDevPacket->data.loop[i].vol.value;
        volAccuracy(expectValue, measuredValue, item);
    }
}


void TestCoreThread::setAlarmCmd(sTestSetCmd &cmd, bool alrm)
{
    if(alrm){
        if(mItem->isSnmp && !cmd.sAlarmMin.isEmpty()) {
            mTrans->setSnmpValue(cmd.sAlarmMin);
            mTrans->setSnmpValue(cmd.sAlarmMax);
            mTrans->snmpUpdateData();
        } else {
            mTrans->setRtuValue(cmd.rtuAlarmMin);
            mTrans->setRtuValue(cmd.rtuAlarmMax);
            mTrans->rtuUpdateData();
        }
    } else {
        //        if(!cmd.sMin.isEmpty()){
        //            mTrans->setSnmpValue(cmd.sMin);
        //            mTrans->setSnmpValue(cmd.sMax);
        //            mTrans->snmpUpdateData();
        //        }
        //        else{
        mTrans->setRtuValue(cmd.rtuMin);
        mTrans->setRtuValue(cmd.rtuMax);
        mTrans->rtuUpdateData();
        //        }
        //        mTrans->rtuStop();
        //        if(mItem->isSnmp) mTrans->snmpStop();
    }
    sleep(14);
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
    int num = mDevPacket->data.lineNum;
    for(int i = 0; i < num; ++i)
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
    if(num <= 0) return;

    setLoopVolCmd(true);
    for(int i = 0; i < num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.loop[i]);
        item.subItem = tr("修改 C%1 电压最小值").arg(i+1);
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
    loopVolAlarm();
}


bool TestCoreThread::curAccuracy(int expect, int measured, sTestDataItem &item, double f)
{
    bool ret = false;
    if(f>10) expect /= COM_RATE_CUR;
    int value = expect - measured;
    item.expect = QString::number(expect / COM_RATE_CUR) + "A";

    int min = -2*COM_RATE_CUR;
    int max =  2*COM_RATE_CUR;
    if( expect != 0 && measured != 0 ) {
        if((value > min) && (value < max)) {
            ret = true;
        }
    }  else
        ret = false;
    item.measured = QString::number(measured / COM_RATE_CUR) + "A";
    item.status = ret ;
    appendResult(item);

    return ret;
}

bool TestCoreThread::curNoCurAccuracy(int expect, int measured, sTestDataItem &item, double f)
{
    bool ret = false;
    if((expect == 0 && measured == 0))  ret = true;
    item.expect = QString::number(expect) + "A";
    item.measured = QString::number(measured / f) + "A";
    item.status = ret;
    appendResult(item);

    return ret;
}

void TestCoreThread::lineNoCur()
{
    sTestDataItem item;
    item.item = tr("相电流检查");

    int num = mDevPacket->data.lineNum;
    for(int i = 0; i < num; ++i) {
        item.subItem = tr("空载, L%1 电流值").arg(i+1);
        int measuredValue = mDevPacket->data.line[i].cur.value;
        curNoCurAccuracy(0, measuredValue, item);
    }
}

void TestCoreThread::loopNoCur()
{
    sTestDataItem item;
    item.item = tr("回路电流检查");

    int num = mDevPacket->data.loopNum;
    for(int i = 0; i < num; ++i) {
        item.subItem = tr(" C%1 电流值").arg(i+1);
        int measuredValue = mDevPacket->data.loop[i].cur.value;
        curNoCurAccuracy(0, measuredValue, item);
    }
}

void TestCoreThread::outputNoCur()
{
    sTestDataItem item;
    item.item = tr("输出位电流检查");
    int num = mDevPacket->data.outputNum;
    for(int i = 0; i < num; ++i) {
        item.subItem = tr("空载输出位 %1 电流值").arg(i+1);
        int measuredValue = mDevPacket->data.output[i].cur.value;
        curNoCurAccuracy(0, measuredValue, item);
    }
}

int TestCoreThread::getLinePorts()
{
    int num = mDevPacket->data.lineNum;
    int outputNum = mDevPacket->data.outputNum;

    if(mDevPacket->devSpec == 1 && mDevPacket->data.lineNum == 1)
        outputNum = 8;
    else if((mDevPacket->devSpec == 1 && mDevPacket->data.lineNum == 2)||
            (mDevPacket->devSpec == 1 && mDevPacket->data.lineNum == 3))
        outputNum = 24;

    return outputNum / num;
}

void TestCoreThread::lineCur()
{
    sTestDataItem item;
    item.item = tr("相电流检查");
    int num = mDevPacket->data.lineNum;
    if( num <= 0 ) return;

    int loop = getLinePorts();
    for(int i = 0; i < num; ++i) {
        item.subItem = tr(" L%1 电流值").arg(i+1);
        int measuredValue = mDevPacket->data.line[i].cur.value;
        int expect = IN_DataPackets::bulid()->getTgCur(i*loop, (i+1)*loop);
        curAccuracy(expect, measuredValue, item, COM_RATE_CUR2);
    }
}

void TestCoreThread::loopCur()
{
    sTestDataItem item;
    item.item = tr("回路电流检查");
    int num = mDevPacket->data.loopNum;
    if(num > 1) {
        item.subItem = tr(" 回路总电流");

        int expect = IN_DataPackets::bulid()->getTgValue(2) ;
        int measuredValue = 0;
        for(int i = 0; i < num; ++i) {
            measuredValue += mDevPacket->data.loop[i].cur.value;
        }
        curAccuracy(expect, measuredValue, item);
    }
    for(int i = 0; i < num; ++i)
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
    for(int i = 0; i < num; ++i)
    {
        item.subItem = tr("小电流输出位 %1 电流值").arg(i+1);
        int measuredValue = mDevPacket->data.output[i].cur.value;
        int expect = IN_DataPackets::bulid()->getObjData(i+8)->cur.value;
        curAccuracy(expect, measuredValue, item , COM_RATE_CUR2);
    }
}


void TestCoreThread::curCheck()
{
    ELoad_RtuSent::bulid()->switchCloseAll(); sleep(10);
    if(mDevPacket->data.lineNum == 1) sleep(10);
    mTrans->snmpUpdateData(); sleep(15);

    lineNoCur();
    loopNoCur();
    if(mDevPacket->devSpec!=3 && mDevPacket->devSpec!=1) {
        outputNoCur();
    }

    ELoad_RtuSent::bulid()->switchOpenAll(); sleep(15);
    if(mDevPacket->data.lineNum == 1) sleep(10);
    mTrans->snmpUpdateData(); sleep(10);

    lineCur();
    loopCur();
    if(mDevPacket->devSpec!=3 && mDevPacket->devSpec!= 1) {
        outputCur();
    }
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
    setLineCurCmd(true); sleep(20);
    mTrans->snmpUpdateData();
    lineCurAlarmDelay();

    int num = mDevPacket->data.lineNum;
    for(int i = 0; i < num; ++i)
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
    if(num <= 0) return;

    setLoopCurCmd(true); sleep(5);
    mTrans->snmpUpdateData(); msleep(500);
    for(int i = 0; i < num; ++i)
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
    if(num <= 0) return;

    setOutputCurCmd(true);
    outputCurAlarmDelay();
    mTrans->snmpUpdateData();
    outputCurAlarmDelay2();

    for(int i = 0; i < num; ++i)
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
    if(mDevPacket->devSpec != 3) {
        outputCurAlarm();
    }
}


bool TestCoreThread::swAccuracy(int measured, sTestDataItem &item , uchar sw , bool isOpen)
{
    bool ret = false;
    QString str = tr("断开");
    if(mDevPacket->devSpec == 3) measured = 0;

    if(isOpen) {
        if(measured || sw) {
            str = tr("接通");
        } else {
            ret = true;
        }
    } else  {
        if(measured || sw) {
            str = tr("接通");
            ret = true;
        }
    }

    item.expect = isOpen == true ? tr("断开") : tr("接通") ;
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
    outputSwCmd(cmd);

    if(alrm){
        mTrans->setSnmpValue(cmd.sAlarmMin);
        mTrans->snmpUpdateData();
    } else{
        mTrans->setSnmpValue(cmd.sAlarmMax);
        mTrans->snmpUpdateData();
    }
}

void TestCoreThread::outputSwCtr()
{
    ELoad_RtuSent::bulid()->switchCloseAll();
    sTestDataItem item;
    item.item = tr("输出位开关控制");
    int num = mDevPacket->data.outputNum;
    if(num <= 0) return;

    setOutputSwCmd(true);
    outputSwCtrDelay();
    for(int i = 0; i < num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.output[i]);
        item.subItem = tr("输出位%1 开关控制 ").arg(i+1);
        int measuredValue = obj->cur.value;//根据电流判断输出位是否断开
        swAccuracy(measuredValue, item , obj->sw , true);
    }

    ELoad_RtuSent::bulid()->switchOpenAll();
    setOutputSwCmd(false);
    outputSwCtrDelay();
    for(int i = 0; i < num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.output[i]);
        item.subItem = tr("输出位%1 开关控制 ").arg(i+1);
        int measuredValue = obj->cur.value;//根据电流判断输出位是否接通
        swAccuracy(measuredValue, item , obj->sw , false);
    }
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
    if( expect != 0 && measured != 0 )
    {
        if((value > min) && (value < max)) {
            ret = true;
        }
    } else {
        ret = false;
    }

    item.expect = QString::number(expect / COM_RATE_POW) + "kVA";
    item.measured = QString::number(measured / COM_RATE_POW) + "kVA";
    item.status = ret;
    appendResult(item);

    return ret;
}

void TestCoreThread::linePow()
{
    int num = mDevPacket->data.lineNum;
    if(num <= 0) return;

    int loop = getLinePorts();
    for(int i = 0; i < num; ++i)
    {
        sTestDataItem item;
        item.item = tr("相功率检查");
        item.subItem = tr(" L %1 功率检查").arg(i+1);
        int expectValue = IN_DataPackets::bulid()->getTgCur(i*loop, (i+1)*loop);
        expectValue *= IN_DataPackets::bulid()->getTgValueByIndex(1,i+1) / COM_RATE_CUR2;
        int measuredValue = mDevPacket->data.line[i].cur.value*mDevPacket->data.line[i].vol.value/COM_RATE_CUR;
        powAccuracy(expectValue, measuredValue, item);
    }
}

void TestCoreThread::loopPow()
{
    int num = mDevPacket->data.loopNum;
    for(int i = 0; i < num; ++i)
    {
        sTestDataItem item;
        item.item = tr("回路功率检查");
        item.subItem = tr(" C %1 功率检查").arg(i+1);
        int expectValue  = -1;
        int measuredValue = mDevPacket->data.loop[i].pow;
        powAccuracy(expectValue, measuredValue, item);
    }
}


int TestCoreThread::getOutputPow(int id)
{
    // mDevPacket->data.output[i].cur.value*mDevPacket->data.line[0].vol.value*mDevPacket->data.output[i].pf/1000;
    return mDevPacket->data.output[id].pow;
}

bool TestCoreThread::outputPow()
{
    bool ret = true;
    sTestDataItem item;
    item.item = tr("输出位功率检查");

    int num = mDevPacket->data.outputNum;
    mTrans->snmpUpdateData(); sleep(10);    ///////防止输出位没有电流
    for(int i = 0; i < num; ++i)
    {
        item.subItem = tr("输出位 %1 功率值").arg(i+1);
        int measuredValue = getOutputPow(i);
        int expect = IN_DataPackets::bulid()->getApPow(i);
        ret = powAccuracy(expect, measuredValue, item);
    }

    return ret;
}

void TestCoreThread::powCheck()
{
    bool ret = true;
    linePow();
    loopPow();

    if(mDevPacket->devSpec!=3) {
        ret = outputPow();
    }
}

bool TestCoreThread::eleAccuracy(int measured, sTestDataItem &item)
{
    bool ret = true;
    if(measured) {
        ret = false;
    }

    item.expect =  "0 kWh";
    item.measured = QString::number(measured / COM_RATE_ELE) + "kWh";
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

    setAlarmCmd(cmd, false);
}


void TestCoreThread::setLineEleCmd()
{
    sTestSetCmd cmd;
    cmd.num = mDevPacket->data.lineNum;
    cmd.devId = mItem->devId;
    lineEleCmd(cmd);

    setAlarmCmd(cmd, false);
}


int TestCoreThread::outputEle()
{
    sTestDataItem item;
    item.item = tr("输出位电能清除");
    int num = mDevPacket->data.outputNum;
    if(num <= 0) return num;

    setOutputEleCmd();
    for(int i = 0; i < num; ++i)
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
    if(num <= 0) return num;

    setLineEleCmd();
    for(int i = 0; i < num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.line[i]);
        item.subItem = tr(" L%1 电能清除 ").arg(i+1);
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
    if(num <= 0) return num;

    for(int i = 0; i < num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.loop[i]);
        item.subItem = tr(" C%1 电能清除 ").arg(i+1);
        int measuredValue = obj->ele;
        eleAccuracy(measuredValue, item);
    }

    return num;
}


void TestCoreThread::eleCheck()
{
    loopEle();
    lineEle();

    //先清开关位电能，接着清回路和相电能
    if(mDevPacket->devSpec != 3) {
        outputEle();
    }
}


bool TestCoreThread::temAccuracy(int expect, int measured, sTestDataItem &item)
{
    bool ret = false;
    int value = expect - measured;
    int min = -5*COM_RATE_TEM;
    int max =  5*COM_RATE_TEM;
    if( expect != 0 && measured != 0 )
    {
        if((value > min) && (value < max)) {
            ret = true;
        }
    } else {
        ret = false;
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
    int min = -5*COM_RATE_HUM;
    int max =  5*COM_RATE_HUM;
    if( expect != 0 && measured != 0 )
    {
        if((value > min) && (value < max)) {
            ret = true;
        }
    }  else {
        ret = false;
    }

    item.expect = QString::number(expect / COM_RATE_HUM) + "%";
    item.measured = QString::number(measured / COM_RATE_HUM) + "%";
    item.status = ret;
    appendResult(item);

    return ret;
}


int TestCoreThread::getEnvs()
{
    return mDevPacket->data.env.envNum;
}

int TestCoreThread::getAvgValue(sDataUnit *unit, int num)
{
    int avgValue = 0 , sum = 0 ,count = 0;
    for(int i = 0; i < num; ++i)
    {
        if(unit[i].value) {
            sum += unit[i].value;
            count++;
        }
    }
    if(count)  avgValue = sum / count;

    return avgValue;
}

void TestCoreThread::temCheck()
{
    int num = getEnvs();
    if(num <= 0) return;

    sTestDataItem item;
    item.item = tr("温度检查");
    int expectValue = getAvgValue(mDevPacket->data.env.tem, num);

    for(int i = 0; i < num; ++i) {
        item.subItem = tr(" 温度%1 ").arg(i+1);
        int measuredValue = mDevPacket->data.env.tem[i].value;
        temAccuracy(expectValue, measuredValue, item);
    }
}

void TestCoreThread::humCheck()
{
    int num = getEnvs();
    if(num <= 0) return;

    sTestDataItem item;
    item.item = tr("湿度检查");
    int expectValue = getAvgValue(mDevPacket->data.env.hum, num);

    for(int i = 0; i < num; ++i) {
        item.subItem = tr(" 湿度%1 ").arg(i+1);
        int measuredValue = mDevPacket->data.env.hum[i].value;
        humAccuracy(expectValue, measuredValue, item);
    }
}

void TestCoreThread::setTemHumAlarmCmd(bool alrm)
{
    sTestSetCmd cmd;
    cmd.num = mDevPacket->data.env.envNum;
    cmd.devId = mItem->devId;
    temHumCmd(cmd);

    setAlarmCmd(cmd, alrm);
}

void TestCoreThread::temHumAlarm()
{
    int num = mDevPacket->data.env.envNum;
    if(num <= 0) return;

    sTestDataItem item;
    item.item = tr("温度湿度告警检查");

    setTemHumAlarmCmd(true);

    for(int i = 0; i < num; ++i)
    {
        sEnvData *obj = &(mDevPacket->data.env);
        item.subItem = tr("修改 温度%1 温度最小值").arg(i+1);
        int expectValue  =  Test_Abnormal_TemMin;
        int measuredValue = obj->tem[i].min;
        temAccuracy(expectValue, measuredValue, item);

        item.subItem = tr("修改 温度%1 温度最大值").arg(i+1);
        expectValue  =  Test_Abnormal_TemMax;
        measuredValue = obj->tem[i].max;
        temAccuracy(expectValue, measuredValue, item);
    }

    for(int i = 0; i < num; ++i)
    {
        sEnvData *obj = &(mDevPacket->data.env);
        item.subItem = tr("修改 湿度%1 湿度最小值").arg(i+1);
        int expectValue  = Test_Abnormal_HumMin;
        int measuredValue = obj->hum[i].min;
        humAccuracy(expectValue, measuredValue, item);

        item.subItem = tr("修改 湿度%1 湿度最大值").arg(i+1);
        expectValue  =  Test_Abnormal_HumMax;
        measuredValue = obj->hum[i].max;
        humAccuracy(expectValue, measuredValue, item);
    }
    setTemHumAlarmCmd(false);
}


void TestCoreThread::envCheck()
{
    temCheck();
    humCheck();
    sensorsCheck();
    temHumAlarm();
}

void TestCoreThread::sensorsCheck()
{
    //暂时把门禁写死为2                     2019/7/25 peng
    int num = getDoors();
    if(num)
    {
        sTestDataItem item;
        item.item = tr("门禁检查");
        for(int i = 0; i < num; ++i)
        {
            item.subItem = tr(" 门禁%1 ").arg(i+1);
            int measuredValue = mDevPacket->data.env.door[i];

            item.expect = tr("正常或者报警");
            item.measured = measuredValue == 0?tr("未接入"):(measuredValue == 1?tr("正常"):tr("报警"));
            item.status = (measuredValue != 0);
            appendResult(item);
        }

        item.item = tr("烟雾检查");
        item.subItem = tr(" 烟雾 ");
        int measuredValue = mDevPacket->data.env.smoke[0];

        item.expect = tr("正常或者报警");
        item.measured = measuredValue == 0?tr("未接入"):(measuredValue == 1?tr("正常"):tr("报警"));
        item.status = (measuredValue != 0);
        appendResult(item);

        item.item = tr("水浸检查");
        item.subItem = tr(" 水浸 ");
        measuredValue = mDevPacket->data.env.water[0];

        item.expect = tr("正常或者报警");
        item.measured = measuredValue == 0?tr("未接入"):(measuredValue == 1?tr("正常"):tr("报警"));
        item.status = (measuredValue != 0);
        appendResult(item);
    }
}

void TestCoreThread::openOrCloseBigCur(bool mode)
{
    for(int i=1; i<4; ++i){
        ELoad_RtuSent::bulid()->setBigCur(i, mode);//打开关闭大电流模式
        msleep(500);
    }
}

bool TestCoreThread::checkOutputZeroCur(int b, sTestDataItem &item)
{
    bool ret = true;
    sDevData *devData = &(mDevPacket->data);
    int expect = devData->output[b].cur.value;
    item.expect = QString::number(expect / COM_RATE_CUR) + "A";
    item.measured = tr("其它输出位有底数:");

    int num = devData->outputNum;
    for(int i = 0; i < num; ++i) {
        if(i != b) {
            int value = devData->output[i].cur.value;
            if(value) {
                item.status = ret = false;
                item.measured += QString::number(i+1) + ". ";
            }
        } else continue;
    }
    if(!ret) appendResult(item);

    return ret;
}


void TestCoreThread::bigCurPowCheck(int i , int addr)
{
    sTestDataItem item;
    item.item = tr("大电流输出位功率检查");//大电流输出位功率检查
    item.subItem = tr("大电流输出位 %1 功率值").arg(i+1);

    //    sDevData *devData = &(mDevPacket->data);
    //    int measuredValue = devData->output[i].cur.value * devData->line[0].vol.value * devData->output[i].pf/1000;
    //    int expect = IN_DataPackets::bulid()->getTgValueByIndex( 3 , addr);

    int measuredValue = getOutputPow(i);
    int expect = IN_DataPackets::bulid()->getTgPow(i, addr);
    powAccuracy(expect, measuredValue, item);
}


void TestCoreThread::setBigCurCmd()
{
    sTestDataItem item;
    sDevData *devData = &(mDevPacket->data);
    int num = devData->outputNum;
    item.item = tr("大电流输出位电流检查");//大电流输出位电流检查

    int nextaddr = 1;
    for(int i = 0; i < num; ++i)
    {
        int index = i/8,bit = i%8,nextbit = 0;
        int addr = index + 1;

        item.subItem = tr("大电流输出位 %1 电流值").arg(i+1);
        bool ret = checkOutputZeroCur(i, item);
        if(ret) {
            int measuredValue = devData->output[i].cur.value;
            int expect = IN_DataPackets::bulid()->getTgValueByIndex( 2 , index+1 );
            curAccuracy(expect, measuredValue, item, COM_RATE_CUR2);
        }
        bigCurPowCheck(i , addr);

        if(bit == 7){
            // for(int j = 0 ; j < 8 ; j++){
            //    ELoad_RtuSent::bulid()->setResData(addr,ELoad_DP_1+j,res[addr*8+j]);
            //    if(addr != 3) ELoad_RtuSent::bulid()->setResData(addr+1,ELoad_DP_1+j,18000);
            //    }
            nextaddr = addr + 1;
            nextbit = 0;
        } else nextbit = bit+1;

        if(i < num-1){
            ELoad_RtuSent::bulid()->switchOpenCtr(nextaddr , nextbit); msleep(50);//打开第i+1位继电器
            ELoad_RtuSent::bulid()->switchOpenCtr(nextaddr , nextbit); msleep(50);//打开第i+1位继电器
            ELoad_RtuSent::bulid()->switchCloseCtr(addr , bit); msleep(50);//关闭第i位继电器
            ELoad_RtuSent::bulid()->switchCloseCtr(addr , bit); msleep(50);//关闭第i位继电器
            mTrans->snmpUpdateData(); bigCurDelay();
        }
    }
}


void TestCoreThread::bigCurCheck()
{
    openOrCloseBigCur(true);//打开大电流模式
    //    QList<int> res;
    //    ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();
    //    for(int i = 1 ; i <= 3 ; i ++)
    //        for(int j = 0 ;j < 8 ; j ++){
    //            res.append(config->getResistance(i,j));
    //        }
    //    for(int i = 0 ; i < 8 ; i++)
    //    {    ELoad_RtuSent::bulid()->setResData(1,ELoad_DP_1+i,18000);
    //    }

    ELoad_RtuSent::bulid()->switchCloseAll(); sleep(15);//关闭所有电子负载的继电器，并且打开第一位
    ELoad_RtuSent::bulid()->switchOpenCtr(1, 0);
    mTrans->snmpUpdateData(); sleep(10);//sleep(30);

    //setBigCurCmd(res);//大电流输出位电流检查
    setBigCurCmd();//大电流输出位电流检查
    openOrCloseBigCur(false);//关闭大电流模式
    ELoad_RtuSent::bulid()->switchOpenAll();
}

void TestCoreThread::openAllOutput()
{
    if((mDevPacket->devSpec != 1) && (mDevPacket->devSpec != 2)) {
        setOutputSwCmd(false); /// 打开PDU所有输出位
        sleep(2);
    }
}

void TestCoreThread::resDev()
{
    //// 这里发送恢复出厂设置命令，清除日志，清除电能等
    ///
    ///
    ///
    sTestSetCmd cmd;
    cmd.devId = mItem->devId;
    clearEleCmd(cmd);

    setFactoryCmd(cmd);
    setAlarmCmd(cmd, false);
}

void current_time_pr(const QString &s)
{
    QDateTime dateTime = QDateTime::currentDateTime();
    qDebug() << s << dateTime.toString("hh:mm:ss");
}

void TestCoreThread::run()
{
    current_time_pr("start");
    bool ret = transmission();  current_time_pr("transmission");
    if(ret)  {
        openAllOutput();    current_time_pr("openAllOutput");
        devInfoCheck();     current_time_pr("devInfoCheck");

        volCheck();     current_time_pr("volCheck");
        curCheck();     current_time_pr("curCheck");
        curAlarmCheck(); current_time_pr("curAlarmCheck");
        powCheck();     current_time_pr("powCheck");

        switchCtr();    current_time_pr("switchCtr");
        // eleCheck();
        envCheck();     current_time_pr("envCheck");

        if(mDevPacket->devSpec != 3 && mDevPacket->devSpec != 1)
            bigCurCheck();  current_time_pr("bigCurCheck");
        //resDev();
    }

    emit overSig();
}
