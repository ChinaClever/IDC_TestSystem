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
extern void current_time_pr(const QString &s);
TestCoreThread::TestCoreThread(QObject *parent) : QThread(parent)
{
    mTrans = nullptr;
    isRun = true;
    mRate = 1;
}

TestCoreThread::~TestCoreThread()
{
    stopThread();
    wait();
    quit();
    terminate();
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
    mDevPacket->txType = 0;
    start();
}

void TestCoreThread::updateData()
{
    if(mItem->isSnmp) {
        mTrans->snmpUpdateData();
    } else {
        mTrans->rtuUpdateData();
    }
    delay(5);
}

void TestCoreThread::stopThread()
{
    isRun = false;
    mTrans->stopRun();
    emit overSig();
}

void TestCoreThread::conditionExec(bool s)
{
    if(mItem->mode == Test_Pause) {
        do{
            mdelay(1);
            if(mItem->mode == Test_Over) break;
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

    mdelay(10);
}


void TestCoreThread::allNumsSlot(int nums)
{  
    sTestProgress *p = &(mItem->progress);
    p->allNum = nums - 1;
}

bool TestCoreThread::appendResult(sTestDataItem &item)
{
    if(!isRun) return false;
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
    int t = snmpTransDelay();
    for(int i=0; i<t; i++) {
        if(isRun) delay(1); else break;
        if(mDevPacket->txType & 0x1) {
            ret = true;
            str = tr("SNMP通讯成功");
            break;
        }
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
    int t = rtuTransDelay();
    for(int i=0; i<t; i++) {
        if(isRun) delay(1); else break;
        if(mDevPacket->txType & 0x2) {
            ret = true;
            str = tr("Modbus通讯成功");
            break;
        }
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

    if(isRun) updateData();
    if(mItem->isSnmp) {
        snmpRet = snmpTrans();
    }
    ret = rtuTrans();

    if(mItem->serialNum.name == "SI-PDU")  snmpRet = true;

    return ret && snmpRet;
}

bool TestCoreThread::volAccuracy(int expect, ushort& measured, sTestDataItem &item)
{
    bool ret = false;

//    int min = -3*COM_RATE_VOL;
//    int max =  3*COM_RATE_VOL;
    int min = -10*COM_RATE_VOL;
    int max =  10*COM_RATE_VOL;
    int t = lineVolAlarmDelay();
    for(int i=0 ; i<t ; i++)
    {
        delay(1);
        int value = expect - measured*mRate;
        if((value >= min) && (value <= max)) {
            ret = true;
            break;
        }
        else {
            ret = false;
        }
    }

    item.expect = QString::number(expect / COM_RATE_VOL) + "V";
    item.measured = QString::number(measured*mRate / COM_RATE_VOL) + "V";
    item.status = ret;
    appendResult(item);

    return ret;
}
double TestCoreThread::autoRate(int vol)
{
    double ret = 1;
    if(vol > 1000 && vol < 3000) {
        ret = 0.1;
    }
    mRate = ret;

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
        autoRate(measuredValue);
        volAccuracy(expectValue, mDevPacket->data.line[i].vol.value, item);
    }
}

void TestCoreThread::loopVol()
{
    int num = mDevPacket->data.loopNum;
    int loop = getLoopPorts();
    if(loop){
        for(int i = 0; i < num; ++i)
        {
            sTestDataItem item;
            item.item = tr("回路电压检查");
            item.subItem = tr(" C%1 电压检查").arg(i+1);
            int expectValue  = IN_DataPackets::bulid()->getTgValueByIndex(1,i/2+1);
            //volAccuracy(expectValue, mDevPacket->data.loop[i].vol.value==0?mDevPacket->data.line[i/2].vol.value:mDevPacket->data.loop[i].vol.value, item);
            volAccuracy(expectValue, mDevPacket->data.loop[i].vol.value, item);
        }
    }
}


void TestCoreThread::setAlarmCmd(sTestSetCmd &cmd, bool alrm)
{
    if(!isRun) return;
    if(alrm){
        if(mItem->isSnmp && !cmd.sAlarmMin.isEmpty()) {
            mTrans->setSnmpValue(cmd.sAlarmMin);
            mTrans->setSnmpValue(cmd.sAlarmMax);
        } else {
            mTrans->setRtuValue(cmd.rtuAlarmMin);
            mTrans->setRtuValue(cmd.rtuAlarmMax);
        }
    } else {
        if(!cmd.sMin.isEmpty()){
            mTrans->setSnmpValue(cmd.sMin);
            mTrans->setSnmpValue(cmd.sMax);
        }
        else{
            mTrans->setRtuValue(cmd.rtuMin);
            mTrans->setRtuValue(cmd.rtuMax);
        }
    }
    delay(14);
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
    int num = mDevPacket->data.lineNum; delay(3);
    for(int i = 0; i < num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.line[i]);
        item.subItem = tr("修改 L%1 电压最小值").arg(i+1);
        int expectValue  = Test_Abnormal_VolMin *COM_RATE_VOL;
        volAccuracy(expectValue, obj->vol.min, item);
    }

    for(int i = 0; i < num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.line[i]);
        item.subItem = tr("修改 L%1 电压最大值").arg(i+1);
        int expectValue  = Test_Abnormal_VolMax *COM_RATE_VOL;
        volAccuracy(expectValue, obj->vol.max, item);
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
        volAccuracy(expectValue, obj->vol.min, item);
    }

    for(int i = 0; i < num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.loop[i]);
        item.subItem = tr("修改 C%1 电压最大值").arg(i+1);
        int expectValue  = Test_Abnormal_VolMax *COM_RATE_VOL;
        volAccuracy(expectValue, obj->vol.max, item);
    }
    setLoopVolCmd(false);
}

void TestCoreThread::volCheck()
{
    lineVol();
    loopVol();
    lineVolAlarm();
    //loopVolAlarm();
}

bool TestCoreThread::curAcc(int expect, int measured, sTestDataItem &item, double f)
{
    bool ret = false;
    int value = f>10?expect/COM_RATE_CUR - measured*mRate:expect- measured*mRate;
    item.expect = QString::number(f>10?expect/COM_RATE_CUR2:expect/COM_RATE_CUR) + "A";

    int min = -3*COM_RATE_VOL;
    int max =  3*COM_RATE_VOL;
    if( expect != 0 && measured != 0 ) {
        if((value > min) && (value < max)) {
            ret = true;
        }
    }

    return ret;
}

bool TestCoreThread::curAcc(int expect,int premeasured, int measured, sTestDataItem &item, double f)
{
    bool ret = false;
    int value = f>10?expect/COM_RATE_CUR - measured*mRate:expect- measured*mRate;
    item.expect = QString::number(f>10?expect/COM_RATE_CUR2:expect/COM_RATE_CUR) + "A";

    int min = -3*COM_RATE_VOL;
    int max =  3*COM_RATE_VOL;
    if( expect != 0 && measured != 0 && premeasured == 0) {
        if((value > min) && (value < max)) {
            ret = true;
        }
    }

    return ret;
}

bool TestCoreThread::curAccuracy(int expect, int measured, sTestDataItem &item, double f)
{
    bool ret = curAcc(expect, measured, item, f);
    item.measured = QString::number(measured*mRate / COM_RATE_CUR) + "A";
    item.status = ret ;
    appendResult(item);

    return ret;
}

bool TestCoreThread::curNoCurAccuracy(int expect, int measured, sTestDataItem &item, double f)
{
    bool ret = false;
    if((expect == 0 && measured == 0))  ret = true;
    item.expect = QString::number(expect) + "A";
    item.measured = QString::number(measured *mRate/ f) + "A";
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
    int loop = getLoopPorts();
    if(loop){
        for(int i = 0; i < num; ++i) {
            item.subItem = tr(" C%1 电流值").arg(i+1);
            int measuredValue = mDevPacket->data.loop[i].cur.value;
            curNoCurAccuracy(0, measuredValue, item);
        }
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

int TestCoreThread::getLoopPorts()
{
    int num = mDevPacket->data.loopNum;
    int outputNum = mDevPacket->data.outputNum;
    int ports = 0;

    if(mDevPacket->devSpec == 1 && mDevPacket->data.lineNum == 1)
        outputNum = 8;
    else if((mDevPacket->devSpec == 1 && mDevPacket->data.lineNum == 2)||
            (mDevPacket->devSpec == 1 && mDevPacket->data.lineNum == 3))
        outputNum = 24;

    if(num > 0)
        ports = outputNum / num;
    return ports;
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

    if( num <= 0 ) return;

    int loop = getLoopPorts();
    if(loop){
        for(int i = 0; i < num; ++i)
        {// 增加假的测试项目
            item.subItem = tr("C%1 电流值").arg(i+1);
            int measuredValue = mDevPacket->data.loop[i].cur.value;
            int expect = 0;
            if(num != 4)
                expect = IN_DataPackets::bulid()->getTgCur(i*loop, (i+1)*loop);
            else{
                loop = mDevPacket->data.outputNum / 6;
                if( i == 0 || i == 3){
                    for(int j = i ; j < i+2 ; j++)
                        expect += IN_DataPackets::bulid()->getTgCur((i==3?j+1:j)*loop, ((i==3?j+1:j)+1)*loop);
                }
                else
                    expect = IN_DataPackets::bulid()->getTgCur((i+1)*loop, (i+1+1)*loop);
            }
            curAccuracy(expect, measuredValue, item , COM_RATE_CUR2);
        }
    }
}

void TestCoreThread::outputCur()
{
    sTestDataItem item;
    item.item = tr("输出位电流检查");

    int num = mDevPacket->data.outputNum;
    for(int i=0; i<num; ++i) {
        item.subItem = tr("小电流输出位 %1 电流值").arg(i+1);
        int measuredValue = mDevPacket->data.output[i].cur.value;
        int expect = IN_DataPackets::bulid()->getObjData(i+8)->cur.value;
        curAccuracy(expect, measuredValue, item , COM_RATE_CUR2);
    }
}


void TestCoreThread::curCheck()
{
    //ELoad_RtuSent::bulid()->switchOpenAll(); delay(15);
    //curCheckDelay();

    lineCur();
    loopCur();
    if(mDevPacket->devSpec!=3 && mDevPacket->devSpec!= 1) {
        outputCur();
    }

    ELoad_RtuSent::bulid()->switchCloseAll(); delay(15);
    int t=curCheckDelay(); delay(t);

    lineNoCur();
    loopNoCur();
    if(mDevPacket->devSpec!=3 && mDevPacket->devSpec!=1) {
        outputNoCur();
    }
    if(isRun) ELoad_RtuSent::bulid()->switchOpenAll();
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
    setLineCurCmd(true); delay(18);//////20

    int num = mDevPacket->data.lineNum;
    for(int i = 0; i < num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.line[i]); delay(1);
        item.subItem = tr("修改 L%1 电流最小值").arg(i+1);
        int expectValue  = Test_Abnormal_CurMin *COM_RATE_CUR;
        curThresholdAccuracy(expectValue, obj->cur.min, item);
    }

    for(int i = 0; i < num; ++i) {
        sObjData *obj = &(mDevPacket->data.line[i]);
        item.subItem = tr("修改 L%1 电流最大值").arg(i+1);
        int expectValue  = Test_Abnormal_CurMax *COM_RATE_CUR;
        curThresholdAccuracy(expectValue, obj->cur.max, item);
    }
    setLineCurCmd(false);
}


void TestCoreThread::loopCurAlarm()
{
    int loop = getLoopPorts();
    if(loop){
        sTestDataItem item;
        item.item = tr("回路电流告警检查");
        int num = mDevPacket->data.loopNum;
        if(num <= 0) return;

        setLoopCurCmd(true); delay(18);
        for(int i = 0; i < num; ++i)
        {
            sObjData *obj = &(mDevPacket->data.loop[i]); delay(1);
            item.subItem = tr("修改 C%1 电流最小值").arg(i+1);
            ushort expectValue  = Test_Abnormal_CurMin *COM_RATE_CUR;
            curThresholdAccuracy(expectValue, obj->cur.min, item);
        }

        for(int i = 0; i < num; ++i) {
            sObjData *obj = &(mDevPacket->data.loop[i]);
            item.subItem = tr("修改 C%1 电流最大值").arg(i+1);
            ushort expectValue  = Test_Abnormal_CurMax *COM_RATE_CUR;
            curThresholdAccuracy(expectValue, obj->cur.max, item);
        }
        setLoopCurCmd(false);
    }
}


bool TestCoreThread::curThresholdAccuracy(ushort expect, ushort &measured, sTestDataItem &item)
{
    bool ret = false;

    int t = outputCurAlarmDelay();
    for(int i=0; i<t; ++i) {
        delay(1);
        if(expect-measured*mRate) {
            ret = false;
        }  else {
            ret = true;
            break;
        }
    }

    item.expect = QString::number(expect/COM_RATE_CUR) + "A";
    item.measured = QString::number(measured *mRate/ COM_RATE_CUR) + "A";
    item.status = ret ;
    appendResult(item);

    return ret;
}

void TestCoreThread::outputCurAlarm()
{
    sTestDataItem item;
    item.item = tr("输出位电流告警检查");
    int num = mDevPacket->data.outputNum;
    if(num <= 0) return;

    setOutputCurCmd(true);
    for(int i=0; i<num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.output[i]);
        item.subItem = tr("修改 输出位%1 电流最小值").arg(i+1);
        ushort expectValue  = Test_Abnormal_CurMin *COM_RATE_CUR;
        curThresholdAccuracy(expectValue, obj->cur.min, item);
    }

    for(int i=0; i<num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.output[i]);
        item.subItem = tr("修改 输出位%1 电流最大值").arg(i+1);
        ushort expectValue  = Test_Abnormal_CurMax *COM_RATE_CUR;
        curThresholdAccuracy(expectValue, obj->cur.max, item);
    }
    setOutputCurCmd(false);
}

void TestCoreThread::curAlarmCheck()
{
    if(!isRun) return;
    lineCurAlarm();
    loopCurAlarm();
    if(mDevPacket->devSpec != 3) {
        outputCurAlarm();
    }
}


bool TestCoreThread::swAccuracy(ushort &measured, sTestDataItem &item , uchar &sw , bool isOpen)
{
    bool ret = false;
    QString str = tr("关");
    if(mDevPacket->devSpec == 3) measured = 0;

    int t = outputSwCtrDelay();
    for(int i=0; i<t; ++i) {
        if(isRun) delay(1); else break;

        if(isOpen) {
            if(measured || sw) {
                str = tr("开");
            } else {
                ret = true;
            }
        } else  {
            if(measured || sw) {
                str = tr("开");
                ret = true;
            }
        }

        if(isOpen){
            if(!ret){
                ret = false;
                str = tr("开");
            } else {
                str = tr("关");
                break;
            }
        }
        else
        {
            if(!ret){
                ret = false;
                str = tr("关");
            } else {
                str = tr("开");
                break;
            }
        }
    }

    item.expect = isOpen == true ? tr("关") : tr("开") ;
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
    } else{
        mTrans->setSnmpValue(cmd.sAlarmMax);
    }
    delay(10);
}

void TestCoreThread::outputSwCtr()
{
    ELoad_RtuSent::bulid()->switchCloseAll();
    sTestDataItem item;
    item.item = tr("输出位开关控制");
    int num = mDevPacket->data.outputNum;
    if(num <= 0) return;

    setOutputSwCmd(true);
    int t=getSwDelay(); delay(t);
    for(int i=0; i<num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.output[i]);
        item.subItem = tr("输出位%1 开关控制 ").arg(i+1);//根据电流判断输出位是否断开
        swAccuracy(obj->cur.value, item , obj->sw , true);
    }

    if(isRun) ELoad_RtuSent::bulid()->switchOpenAll();
    setOutputSwCmd(false); delay(2);
    for(int i = 0; i < num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.output[i]);
        item.subItem = tr("输出位%1 开关控制 ").arg(i+1);//根据电流判断输出位是否接通
        swAccuracy(obj->cur.value, item , obj->sw , false);
    }
}


void TestCoreThread::switchCtr()
{
    if((mDevPacket->devSpec != 1) && (mDevPacket->devSpec != 2))
        if(isRun) outputSwCtr();
}


bool TestCoreThread::powAccuracy(int expect, int measured, sTestDataItem &item,QString str)
{
    bool ret = false;
    int value = expect - measured;
    int min = -5*COM_RATE_CUR2;
    int max =  5*COM_RATE_CUR2;
    if( expect != 0 && measured != 0 )
    {
        if((value > min) && (value < max)) {
            ret = true;
        }
    } else {
        ret = false;
    }

    item.expect = QString::number(expect / COM_RATE_POW) + str;
    item.measured = QString::number(measured / COM_RATE_POW) + str;
    item.status = ret;
    appendResult(item);

    return ret;
}

bool TestCoreThread::powBigAccuracy(int expect, ushort *measured, sTestDataItem &item, QString str)
{
    bool ret = false;

    int t = getCheckPow();
    for(int i = 0 ; i < t ; i++){
        delay(1);
        int value = expect/10 - *measured/10;
        int min = -8*COM_RATE_VOL;
        int max =  8*COM_RATE_VOL;
        if( expect != 0 && *measured != 0 )
        {
            if((value > min) && (value < max)) {
                ret = true;
                break;
            }else {
                ret = false;
            }
        }else {
            ret = false;
        }
    }

    item.expect = QString::number(expect / COM_RATE_POW) + str;
    item.measured = QString::number(*measured / COM_RATE_POW) + str;
    item.status = ret;
    appendResult(item);

    return ret;
}

bool TestCoreThread::getLinePow(int id, int &measure)
{
    measure = mDevPacket->data.line[id].pow;
    return true;
}

void TestCoreThread::linePow()
{
    int num = mDevPacket->data.lineNum;
    if(num <= 0) return;

    int loop = getLinePorts();
    QString str ="kVA";
    for(int i = 0; i < num; ++i)
    {
        sTestDataItem item;
        item.item = tr("相功率检查");
        item.subItem = tr(" L %1 功率检查").arg(i+1);

        int measuredValue = 0;
        bool powOrActivePowFlag = false;
        powOrActivePowFlag = getLinePow(i,measuredValue);

        int expectValue = IN_DataPackets::bulid()->getTgCur(i*loop, (i+1)*loop);
        expectValue *= IN_DataPackets::bulid()->getTgValueByIndex(1,i+1) / COM_RATE_CUR2;

        if(powOrActivePowFlag) {
            expectValue = IN_DataPackets::bulid()->getTgPowByStratAndEnd(i*loop, (i+1)*loop);
            str = "kW";
        }
        powAccuracy(expectValue, measuredValue, item ,str);
    }
}

bool TestCoreThread::getLoopPow(int id, int &measure)
{
    measure = mDevPacket->data.loop[id].pow;
    return true;
}

void TestCoreThread::loopPow()
{
    int num = mDevPacket->data.loopNum;
    if(num <= 0) return;

    QString str ="kVA";
    int loop = getLoopPorts();
    if(loop){
        for(int i = 0; i < num; ++i)
        {
            sTestDataItem item;
            item.item = tr("回路功率检查");
            item.subItem = tr(" C %1 功率检查").arg(i+1);
            int measuredValue = 0;
            bool powOrActivePowFlag=false;
            powOrActivePowFlag = getLoopPow(i,measuredValue);
            int expectValue  = 0;
            if(num != 4)
                expectValue = IN_DataPackets::bulid()->getTgCur(i*loop, (i+1)*loop);
            else{
                loop = mDevPacket->data.outputNum / 6;
                if( i == 0 || i == 3){
                    for(int j = i ; j < i+2 ; j++)
                        expectValue += IN_DataPackets::bulid()->getTgCur((i==3?j+1:j)*loop, ((i==3?j+1:j)+1)*loop);
                }
                else
                    expectValue = IN_DataPackets::bulid()->getTgCur((i+1)*loop, (i+1+1)*loop);
            }
            expectValue *= IN_DataPackets::bulid()->getTgValueByIndex(1,i/2+1) / COM_RATE_CUR2;

            if(powOrActivePowFlag) {
                expectValue = IN_DataPackets::bulid()->getTgPowByStratAndEnd(i*loop, (i+1)*loop);
                str = "kW";
            }

            powAccuracy(expectValue, measuredValue, item ,str);
        }
    }
}


bool TestCoreThread::getOutputPow(int id , ushort &measure)
{
    if( mDevPacket->data.output[id].pow){
        measure = mDevPacket->data.output[id].pow;
        return true;
    }else{
        measure = mDevPacket->data.output[id].activePow;
        return false;
    }
}

bool TestCoreThread::getBigOutputPow(int id , ushort **measure)
{
    if( mDevPacket->data.output[id].pow){
        *measure = &(mDevPacket->data.output[id].pow);
        return true;
    }else{
        *measure = &(mDevPacket->data.output[id].activePow);
        return false;
    }
}

bool TestCoreThread::outputPow()
{
    bool ret = true;
    sTestDataItem item;
    item.item = tr("输出位功率检查");

    QString str = "kVA";
    int num = mDevPacket->data.outputNum; delay(10);    ///////防止输出位没有电流
    for(int i = 0; i < num; ++i)
    {
        item.subItem = tr("输出位 %1 功率值").arg(i+1);
        bool powOrActivePowFlag=false;
        ushort measuredValue = 0;
        powOrActivePowFlag = getOutputPow(i,measuredValue);
        int expect = IN_DataPackets::bulid()->getApPow(i);
        if(powOrActivePowFlag) {
            expect = IN_DataPackets::bulid()->getObjData(i+8)->pow;
            str = "kW";
        }
        ret = powAccuracy(expect, measuredValue, item , str);
    }

    return ret;
}

void TestCoreThread::powCheck()
{
    linePow();
    loopPow();

    if(mDevPacket->devSpec!=3) {
        outputPow();
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
//    int min = -5*COM_RATE_TEM;
//    int max =  5*COM_RATE_TEM;
    int min = -50*COM_RATE_TEM;
    int max =  50*COM_RATE_TEM;
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
//    int min = -5*COM_RATE_HUM;
//    int max =  5*COM_RATE_HUM;
    int min = -50*COM_RATE_HUM;
    int max =  50*COM_RATE_HUM;
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
    //temHumAlarm();
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
        if(isRun) ELoad_RtuSent::bulid()->setBigCur(i, mode);//打开关闭大电流模式
        mdelay(600);
    }
}

bool TestCoreThread::checkOutputZeroCur(int b, sTestDataItem &item, bool flag)
{
    bool ret = true;
    sDevData *devData = &(mDevPacket->data);
    int expect = IN_DataPackets::bulid()->getTgValueByIndex(2, b/8+1);
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
    if(!ret&&flag) appendResult(item);

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

    ushort zero = 0;
    ushort *pzero = &zero;
    ushort **measuredValue=&pzero;
    bool powOrActivePowFlag=false;
    sleep(getCheckActivePow());
    QString str = "kVA";
    powOrActivePowFlag = getBigOutputPow(i,measuredValue);
    if(powOrActivePowFlag) str = "kW";
    int expect = IN_DataPackets::bulid()->getTgPow(i, addr , powOrActivePowFlag);
    powBigAccuracy(expect, *measuredValue, item , str);
}


bool TestCoreThread::curBigAccuracy(ushort index,ushort *premeasured, ushort *measured, sTestDataItem &item)
{
    bool ret = false;
    ushort expect = 0;
    int t = bigCurDelay();
    for(int i=0; i< t; ++i){
        delay(1);
        expect = IN_DataPackets::bulid()->getTgValueByIndex(2, index+1);
        ret = curAcc(expect,*premeasured, *measured, item, COM_RATE_CUR2);
        if(ret) break;
    }

    return ret;
}


void TestCoreThread::setBigCurCmd()
{
    sTestDataItem item;
    sDevData *devData = &(mDevPacket->data);
    int num = devData->outputNum;
    item.item = tr("大电流输出位电流检查");//大电流输出位电流检查

    int nextaddr = 1;
    for(int i=0; i<num; ++i)
    {
        int index = i/8,bit = i%8,nextbit = 0;
        int addr = index + 1;

        item.subItem = tr("大电流输出位 %1 电流值").arg(i+1);
        ushort *measuredValue = &(devData->output[i].cur.value);
        ushort zero = 0;
        ushort *preMeasuredValue;
        preMeasuredValue = &zero;
        if(i >= 1) preMeasuredValue = &(devData->output[i-1].cur.value);
        curBigAccuracy(index,preMeasuredValue, measuredValue, item);
        bool ret = checkOutputZeroCur(i, item);
        if(ret) {
            int expect = IN_DataPackets::bulid()->getTgValueByIndex(2, index+1);
            curAccuracy(expect, *measuredValue, item, COM_RATE_CUR2);
        }
        else{
            curBigAccuracy(index,preMeasuredValue, measuredValue, item);
            ret = checkOutputZeroCur(i, item , true);
            if(ret) {
                int expect = IN_DataPackets::bulid()->getTgValueByIndex(2, index+1);
                curAccuracy(expect, *measuredValue, item, COM_RATE_CUR2);
            }
        }
        if(isRun) bigCurPowCheck(i , addr);

        bool noDelayFlag = true;
        if(bit == 7 && addr < 3){
            // for(int j = 0 ; j < 8 ; j++){
            //    ELoad_RtuSent::bulid()->setResData(addr,ELoad_DP_1+j,res[addr*8+j]);
            //    if(addr != 3) ELoad_RtuSent::bulid()->setResData(addr+1,ELoad_DP_1+j,18000);
            //    }
            nextaddr = addr + 1;
            nextbit = 0;
            if(!mItem->serialNum.isDelayBreaker){
                controlNoDelayBreaker(nextaddr);
                noDelayFlag = false;
                int t=firstOpDelay();//35
                delay(t);
            }
        } else {
            nextbit = bit+1;
            noDelayFlag = true;
        }

        if(i < num-1 && noDelayFlag && isRun){
            if(isRun) ELoad_RtuSent::bulid()->switchOpenCtr(nextaddr, nextbit); mdelay(50);//打开第i+1位继电器
            if(isRun) ELoad_RtuSent::bulid()->switchOpenCtr(nextaddr, nextbit); mdelay(50);//打开第i+1位继电器
            if(isRun) ELoad_RtuSent::bulid()->switchCloseCtr(addr, bit); mdelay(50);//关闭第i位继电器
            if(isRun) ELoad_RtuSent::bulid()->switchCloseCtr(addr, bit); delay(5);//关闭第i位继电器
        }
        if(!isRun) break;
    }
}

void TestCoreThread::bigCurCheck()
{
    if(mItem->serialNum.isDelayBreaker){
        if(isRun) openOrCloseBigCur(true);//打开大电流模式
        //    QList<int> res;
        //    ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();
        //    for(int i = 1 ; i <= 3 ; i ++)
        //        for(int j = 0 ;j < 8 ; j ++){
        //            res.append(config->getResistance(i,j));
        //        }
        //    for(int i = 0 ; i < 8 ; i++)
        //    {    ELoad_RtuSent::bulid()->setResData(1,ELoad_DP_1+i,18000);
        //    }

        if(isRun) ELoad_RtuSent::bulid()->switchCloseAll(); delay(15);//关闭所有电子负载的继电器，并且打开第一位
        if(isRun) ELoad_RtuSent::bulid()->switchOpenCtr(1, 0);delay(firstOpDelay()); ///====20
    }else{
        if(isRun) ELoad_RtuSent::bulid()->switchCloseAll(); delay(15);//关闭所有电子负载的继电器
        if(isRun) controlNoDelayBreaker(1);delay(firstOpDelay());
    }

    //setBigCurCmd(res);//大电流输出位电流检查
    if(isRun) setBigCurCmd();//大电流输出位电流检查
    openOrCloseBigCur(false);//关闭大电流模式
    if(isRun) ELoad_RtuSent::bulid()->switchOpenAll();
}

void TestCoreThread::controlNoDelayBreaker(int id)
{
    if( id <= 0 && !isRun) return;
    if(id>=2)
    {
        if(isRun) ELoad_RtuSent::bulid()->setBigCur(id-1, false); mdelay(600);//关闭大电流模式
        if(isRun) ELoad_RtuSent::bulid()->switchCloseCtr(id-1, 7); mdelay(50);
        if(isRun) ELoad_RtuSent::bulid()->switchCloseCtr(id-1, 7); mdelay(50);
    }
    for(int i = 0 ; i < 8; i++)
    {
        if(isRun) ELoad_RtuSent::bulid()->switchOpenCtr(id, i); mdelay(50);
        if(isRun) ELoad_RtuSent::bulid()->switchOpenCtr(id, i); mdelay(50);
    }
    if(isRun) ELoad_RtuSent::bulid()->setBigCur(id, true); mdelay(600);//打开大电流模式


    for(int i = 1 ; i < 8; i++)
    {
        if(isRun) ELoad_RtuSent::bulid()->switchCloseCtr(id, i); mdelay(50);
        if(isRun) ELoad_RtuSent::bulid()->switchCloseCtr(id, i); mdelay(50);
    }
    delay(5);
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


void TestCoreThread::initSwitch()
{
    isRun = true;
    mTrans->startRun();
    ELoad_RtuSent::bulid()->switchOpenAll();
    if((mDevPacket->devSpec != 1) && (mDevPacket->devSpec != 2)) {
        setOutputSwCmd(false); /// 打开PDU所有输出位
    }
}

void TestCoreThread::run()
{
    initSwitch();
    bool ret = transmission();
    if(ret)  {
        if(isRun) devInfoCheck();
        if(isRun) volCheck();
        if(isRun) powCheck();
        if(isRun) curCheck();
        if(isRun) curAlarmCheck();

        if(isRun) switchCtr();
        // if(isRun) eleCheck();
        if(isRun) envCheck();

        if(mDevPacket->devSpec != 3 && mDevPacket->devSpec != 1)
            if(isRun) bigCurCheck();
        //resDev();
    }

    emit overSig();
}
