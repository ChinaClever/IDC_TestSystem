/*
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
    mItem->mode = Test_Over;
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
    p->status = str;

    ///=========== 测试项目
    p->allNum = 200;
    msleep(600);
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
    mTrans->snmpUpdateData(); sleep(8);
    if(mDevPacket->offLine) {
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
    mTrans->rtuUpdateData(); sleep(5);
    if(mDevPacket->offLine) {
        ret = true;
        str = tr("Modbus通讯成功");
    }

    item.status = ret;
    item.measured = str;
    //    mTrans->rtuStop();

    return appendResult(item);
}

bool TestCoreThread::transmission()
{
    bool ret = true;

    if(mItem->isSnmp) ret = snmpTrans();
    if(ret) ret = rtuTrans();

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
        int expectValue  = IN_DataPackets::bulid()->getLineVol(i) ;
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
        int expectValue  = IN_DataPackets::bulid()->getLineVol(i) ;
        int measuredValue = mDevPacket->data.loop[i].vol.value;
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
        mTrans->setRtuValue(cmd.rtuMin);
        mTrans->setRtuValue(cmd.rtuMax);

//        mTrans->rtuStop();
//        if(mItem->isSnmp) mTrans->snmpStop();
    }
    sleep(5);
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
        sleep(1);
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
        sleep(1);
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
    item.status = ret;
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
    item.subItem = tr(" 相总电流");

    int expect = IN_DataPackets::bulid()->getTgValue(2) ;
    int num = mDevPacket->data.lineNum;
    int measuredValue = 0;
    for(int i=0; i<num; ++i) {
        measuredValue += mDevPacket->data.line[i].cur.value;
    }
    curAccuracy(expect, measuredValue, item);
}

void TestCoreThread::loopCur()
{
    sTestDataItem item;
    item.item = tr("回路电流检查");
    item.subItem = tr(" 回路总电流");

    int expect = IN_DataPackets::bulid()->getTgValue(2) ;
    int num = mDevPacket->data.loopNum;
    int measuredValue = 0;
    for(int i=0; i<num; ++i) {
        measuredValue += mDevPacket->data.loop[i].cur.value;
    }
    curAccuracy(expect, measuredValue, item);
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
        int expect = IN_DataPackets::bulid()->getObjData(i)->cur.value;
        curAccuracy(expect, measuredValue, item);
    }
}


void TestCoreThread::curCheck()
{
    ELoad_RtuSent::bulid()->switchCloseAll();
    sleep(5); updateData(); sleep(2);
    lineNoCur();
    loopNoCur();
    outputNoCur();

    ELoad_RtuSent::bulid()->switchOpenAll();
    sleep(5); updateData(); sleep(2);
    lineCur();
    loopCur();
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
        sleep(1);
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
        sleep(1);
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
        sleep(1);
    }
    setOutputCurCmd(false);
}

void TestCoreThread::curAlarmCheck()
{
    lineCurAlarm();
    loopCurAlarm();
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
    outputSwCmd(cmd);

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
        sleep(1);
    }
    setOutputSwCmd(false);
}


void TestCoreThread::switchCtr()
{
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
        item.item = tr("回路电压检查");
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
        int measuredValue = mDevPacket->data.output[i].pow;
        int expect = IN_DataPackets::bulid()->getObjData(i)->pow;
        bool r = powAccuracy(expect, measuredValue, item);
        if(r == false) ret = false;
    }

    return ret;
}

void TestCoreThread::powCheck()
{
    bool ret = outputPow();
    if(ret) {
        linePow();
        loopPow();
    }
}

bool TestCoreThread::eleAccuracy(int measured, sTestDataItem &item)
{
    bool ret = true;
    QString str = tr("断开");
    if(measured) {
        ret = false;
    }

    item.expect =  "0 KWh";
    item.measured = QString::number(measured / COM_RATE_POW) + "KWh";
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
        sleep(1);
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
        sleep(1);
    }

    return num;
}


void TestCoreThread::eleCheck()
{
    outputEle();
    lineEle();
}

void TestCoreThread::run()
{
    transmission();

    volCheck();
    curCheck();
    curAlarmCheck();

    switchCtr();
    eleCheck();
    powCheck();
}
