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
    mRate = 1;
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

    msleep(10);
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
    int t = snmpTransDelay();
    for(int i=0; i<t; i++) {
        sleep(1);
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
        sleep(1);
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

    updateData();
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

    int min = -3*COM_RATE_VOL;
    int max =  3*COM_RATE_VOL;
    int t = lineVolAlarmDelay();
    for(int i=0 ; i<t ; i++)
    {
        sleep(1);
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


void TestCoreThread::setAlarmCmd(sTestSetCmd &cmd, bool alrm)
{
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
    sleep(3);
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

    int min = -2*COM_RATE_CUR;
    int max =  2*COM_RATE_CUR;
    if( expect != 0 && measured != 0 ) {
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

    int loop = getLinePorts();
    for(int i = 0; i < num; ++i)
    {// 增加假的测试项目
        item.subItem = tr("C%1 电流值").arg(i+1);
        int measuredValue = mDevPacket->data.loop[i].cur.value;
        int expect = IN_DataPackets::bulid()->getTgCur(i*loop, (i+1)*loop);
        curAccuracy(expect, measuredValue, item , COM_RATE_CUR2);
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
    //ELoad_RtuSent::bulid()->switchOpenAll(); sleep(15);
    //curCheckDelay();

    lineCur();
    loopCur();
    if(mDevPacket->devSpec!=3 && mDevPacket->devSpec!= 1) {
        outputCur();
    }

    ELoad_RtuSent::bulid()->switchCloseAll(); sleep(15);
    curCheckDelay();

    lineNoCur();
    loopNoCur();
    if(mDevPacket->devSpec!=3 && mDevPacket->devSpec!=1) {
        outputNoCur();
    }
    ELoad_RtuSent::bulid()->switchOpenAll();
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
    setLineCurCmd(true); sleep(18);//////20

    int num = mDevPacket->data.lineNum;
    for(int i = 0; i < num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.line[i]); sleep(1);
        item.subItem = tr("修改 L%1 电流最小值").arg(i+1);
        int expectValue  = Test_Abnormal_CurMin *COM_RATE_CUR;
        int measuredValue = obj->cur.min;
        curAccuracy(expectValue, measuredValue, item);
    }

    for(int i = 0; i < num; ++i) {
        sObjData *obj = &(mDevPacket->data.line[i]);
        item.subItem = tr("修改 L%1 电流最大值").arg(i+1);
        int expectValue  = Test_Abnormal_CurMax *COM_RATE_CUR;
        int measuredValue = obj->cur.max;
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

    setLoopCurCmd(true); sleep(18);
    for(int i = 0; i < num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.loop[i]); sleep(1);
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


bool TestCoreThread::curThresholdAccuracy(ushort expect, ushort &measured, sTestDataItem &item)
{
    bool ret = false;

    int t = outputCurAlarmDelay();
    for(int i=0; i<t; ++i) {
        sleep(1);
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
        sleep(1);
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
    sleep(10);
}

void TestCoreThread::outputSwCtr()
{
    ELoad_RtuSent::bulid()->switchCloseAll();
    sTestDataItem item;
    item.item = tr("输出位开关控制");
    int num = mDevPacket->data.outputNum;
    if(num <= 0) return;

    setOutputSwCmd(true); sleep(5);
    for(int i=0; i<num; ++i)
    {
        sObjData *obj = &(mDevPacket->data.output[i]);
        item.subItem = tr("输出位%1 开关控制 ").arg(i+1);//根据电流判断输出位是否断开
        swAccuracy(obj->cur.value, item , obj->sw , true);
    }

    ELoad_RtuSent::bulid()->switchOpenAll();
    setOutputSwCmd(false); sleep(2);
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

int TestCoreThread::getLinePow(int id)
{
    return mDevPacket->data.line[id].pow;
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

        int measuredValue = getLinePow(i);
        powAccuracy(expectValue, measuredValue, item);
    }
}

void TestCoreThread::loopPow()
{
    int num = mDevPacket->data.loopNum;
    if(num <= 0) return;

    int loop = getLinePorts();
    for(int i = 0; i < num; ++i)
    {
        sTestDataItem item;
        item.item = tr("回路功率检查");
        item.subItem = tr(" C %1 功率检查").arg(i+1);
        int expectValue  = IN_DataPackets::bulid()->getTgCur(i*loop, (i+1)*loop);
        expectValue *= IN_DataPackets::bulid()->getTgValueByIndex(1,i+1) / COM_RATE_CUR2;
        int measuredValue = mDevPacket->data.loop[i].activePow;
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

    int num = mDevPacket->data.outputNum; sleep(10);    ///////防止输出位没有电流
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
        ELoad_RtuSent::bulid()->setBigCur(i, mode);//打开关闭大电流模式
        msleep(600);
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

    int measuredValue = getOutputPow(i);
    int expect = IN_DataPackets::bulid()->getTgPow(i, addr);
    powAccuracy(expect, measuredValue, item);
}


bool TestCoreThread::curBigAccuracy(ushort index, ushort *measured, sTestDataItem &item)
{
    bool ret = false;
    ushort expect = 0;
    int t = bigCurDelay();
    for(int i=0; i< t; ++i){
        sleep(1);
        expect = IN_DataPackets::bulid()->getTgValueByIndex(2, index+1);
        ret = curAcc(expect, *measured, item, COM_RATE_CUR2);
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
        curBigAccuracy(index, measuredValue, item);
        bool ret = checkOutputZeroCur(i, item);
        if(ret) {
            int expect = IN_DataPackets::bulid()->getTgValueByIndex(2, index+1);
            curAccuracy(expect, *measuredValue, item, COM_RATE_CUR2);
        }
        else{
            curBigAccuracy(index, measuredValue, item);
            ret = checkOutputZeroCur(i, item , true);
            if(ret) {
            int expect = IN_DataPackets::bulid()->getTgValueByIndex(2, index+1);
            curAccuracy(expect, *measuredValue, item, COM_RATE_CUR2);
            }
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
            ELoad_RtuSent::bulid()->switchOpenCtr(nextaddr, nextbit); msleep(50);//打开第i+1位继电器
            ELoad_RtuSent::bulid()->switchOpenCtr(nextaddr, nextbit); msleep(50);//打开第i+1位继电器
            ELoad_RtuSent::bulid()->switchCloseCtr(addr, bit); msleep(50);//关闭第i位继电器
            ELoad_RtuSent::bulid()->switchCloseCtr(addr, bit); sleep(3);//关闭第i位继电器
            //  bigCurDelay();
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
    ELoad_RtuSent::bulid()->switchOpenCtr(1, 0);sleep(20); ///====

    //setBigCurCmd(res);//大电流输出位电流检查
    setBigCurCmd();//大电流输出位电流检查
    openOrCloseBigCur(false);//关闭大电流模式
    ELoad_RtuSent::bulid()->switchOpenAll();
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
    ELoad_RtuSent::bulid()->switchOpenAll();
    if((mDevPacket->devSpec != 1) && (mDevPacket->devSpec != 2)) {
        setOutputSwCmd(false); /// 打开PDU所有输出位
    }
}

void TestCoreThread::run()
{
    current_time_pr("start");
    initSwitch();    current_time_pr("initSwitch");
    bool ret = transmission();  current_time_pr("transmission");
    if(ret)  {
        devInfoCheck();     current_time_pr("devInfoCheck");
        volCheck();     current_time_pr("volCheck");
        powCheck();     current_time_pr("powCheck");
        curCheck();     current_time_pr("curCheck");
        curAlarmCheck(); current_time_pr("curAlarmCheck");

        switchCtr();    current_time_pr("switchCtr");
        // eleCheck();
        envCheck();     current_time_pr("envCheck");

        if(mDevPacket->devSpec != 3 && mDevPacket->devSpec != 1)
            bigCurCheck();  current_time_pr("bigCurCheck");
        //resDev();
    }

    emit overSig();
}
