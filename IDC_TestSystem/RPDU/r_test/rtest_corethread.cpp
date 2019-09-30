/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "rtest_corethread.h"
#include "r_snmp/r_snmptrans.h"
#include "r_rtu/r_rturegenum.h"
#include "eload_com/in_datapackets.h"

RTest_CoreThread::RTest_CoreThread(QObject *parent) : TestCoreThread(parent)
{

}


int RTest_CoreThread::getLineNum()
{
    int line = mDevPacket->data.lineNum;
    line = line == 2 ? line-1 : line;

    return line;
}

int RTest_CoreThread::getLoopNum()
{
    int count = 0;
    mDevPacket->data.loopNum = count;
    if(mDevPacket->data.lineNum < 3) {
        for(int i = 0 ; i < 3 ; i++)
            if(mDevPacket->data.line[i].vol.value != 0) count++;
    }  else {
        count = 3;
    }

    return count;
}

int RTest_CoreThread::getLinePorts()
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

int RTest_CoreThread::outputSwCtrDelay()
{
//    int num = mDevPacket->data.outputNum;

//    sleep(15*(num/8));
//    if(num/8 == 1) sleep(10);//水平8位需要延时长点
    return 60;
}

bool RTest_CoreThread::curBigAccuracy(ushort index, ushort *measured, sTestDataItem &item)
{
    bool ret = false;
    ushort expect = 0;
    int count = 0;
    int t = bigCurDelay();
    for(int i=0; i< t; ++i){
        sleep(1);
        expect = IN_DataPackets::bulid()->getTgValueByIndex(2, index+1);
        ret = curAcc(expect, *measured, item, COM_RATE_CUR2);
        if(ret && count == 6) break;
        else if(ret) count++;
    }

    return ret;
}

int RTest_CoreThread::getOutputPow(int id)
{
    return mDevPacket->data.output[id].cur.value*mDevPacket->data.line[0].vol.value/COM_RATE_CUR;
}

int RTest_CoreThread::getEnvs()
{
    int num=4, outputNum = mDevPacket->data.outputNum;
    if(mItem->serialNum.name == "RPDU")
    {
        if(mDevPacket->devSpec == 1 && mDevPacket->data.lineNum == 1)
            outputNum = 8;
        else if((mDevPacket->devSpec == 1 && mDevPacket->data.lineNum == 2)||
                (mDevPacket->devSpec == 1 && mDevPacket->data.lineNum == 3))
            outputNum = 24;
    }
    if(mDevPacket->data.lineNum == 1 && outputNum == 8)//水平只检测2个温湿度
        num = 2;

    return num;
}

int RTest_CoreThread::getDoors()
{
    int num = 2;
    int outputNum = mDevPacket->data.outputNum;
    if(mItem->serialNum.name == "RPDU")
    {
        if(mDevPacket->devSpec == 1 && mDevPacket->data.lineNum == 1)
            outputNum = 8;
        else if((mDevPacket->devSpec == 1 && mDevPacket->data.lineNum == 2)||
                (mDevPacket->devSpec == 1 && mDevPacket->data.lineNum == 3))
            outputNum = 24;
    }
    if(mDevPacket->data.lineNum == 1 && outputNum == 8)//水平只检测2个温湿度
        num = 0;

    return num;
}

void RTest_CoreThread::curCheckDelay()
{
    if(mDevPacket->data.lineNum == 1) sleep(10);
    sleep(45);
}

bool RTest_CoreThread::lineVolCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;

    for(int i=0; i<it.num; ++i) {
        //        snmpCmd.oid = QString("%1.%2.%3.1.%4.8.0").arg(MIB_OID_CLEVER).arg(R_MIB_OID).arg(addr).arg(i+3);
        //        snmpCmd.value = QString::number(Test_Abnormal_VolMin).toUtf8(); it.sAlarmMin.append(snmpCmd);
        //        snmpCmd.value = QString::number(Test_Normal_VolMin).toUtf8();  it.sMin.push_front(snmpCmd);

        rtuCmd.reg = R_RtuReg_LineVolMin+i;
        rtuCmd.value = Test_Normal_VolMin; it.rtuMin.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_VolMin; it.rtuAlarmMin.append(rtuCmd);

        //        snmpCmd.oid = QString("%1.%2.%3.1.%4.9.0").arg(MIB_OID_CLEVER).arg(R_MIB_OID).arg(addr).arg(i+3);
        //        snmpCmd.value = QString::number(Test_Abnormal_VolMax).toUtf8(); it.sAlarmMax.append(snmpCmd);
        //        snmpCmd.value = QString::number(Test_Normal_VolMax).toUtf8();  it.sMax.push_front(snmpCmd);

        rtuCmd.reg = R_RtuReg_LineVolMax+i;
        rtuCmd.value = Test_Normal_VolMax; it.rtuMax.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_VolMax; it.rtuAlarmMax.append(rtuCmd);
    }

    return true;
}

bool RTest_CoreThread::loopVolCmd(sTestSetCmd &it)
{

    return true;
}

bool RTest_CoreThread::lineCurCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;

    for(int i=0; i<it.num; ++i) {
        //        snmpCmd.oid = QString("%1.%2.%3.1.%4.6.0").arg(MIB_OID_CLEVER).arg(R_MIB_OID).arg(addr).arg(i+3);
        //        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMin).toUtf8(); it.sAlarmMin.append(snmpCmd);
        //        snmpCmd.value = QString("%1.0").arg(Test_Normal_CurMin).toUtf8();  it.sMin.push_front(snmpCmd);

        rtuCmd.reg = R_RtuReg_LineCurMin+i;
        rtuCmd.value = Test_Normal_CurMin*COM_RATE_CUR; it.rtuMin.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMin*COM_RATE_CUR; it.rtuAlarmMin.append(rtuCmd);

        //        snmpCmd.oid = QString("%1.%2.%3.1.%4.7.0").arg(MIB_OID_CLEVER).arg(R_MIB_OID).arg(addr).arg(i+3);
        //        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMax).toUtf8(); it.sAlarmMax.append(snmpCmd);
        //        snmpCmd.value = QString("%1.0").arg(Test_Normal_LineCurMax).toUtf8();  it.sMax.push_front(snmpCmd);

        rtuCmd.reg = R_RtuReg_LineCurMax+i;
        rtuCmd.value = Test_Abnormal_CurMax*COM_RATE_CUR; it.rtuMax.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMax*COM_RATE_CUR; it.rtuAlarmMax.append(rtuCmd);
    }

    return true;
}


bool RTest_CoreThread::loopCurCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;

    for(int i=0; i<it.num; ++i) {

    }

    return true;
}


bool RTest_CoreThread::outputCurCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;

    for(int i=0; i<it.num; ++i) {
        //        snmpCmd.oid = QString("%1.%2.%3.1.11.%4.0").arg(MIB_OID_CLEVER).arg(R_MIB_OID).arg(addr).arg(i+1);
        //        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMin).toUtf8(); it.sAlarmMin.append(snmpCmd);
        //        snmpCmd.value = QString("%1.0").arg(Test_Normal_CurMin).toUtf8();  it.sMin.push_front(snmpCmd);

        rtuCmd.reg = R_RtuReg_OutputCurMin+i;
        rtuCmd.value = Test_Normal_CurMin*COM_RATE_CUR; it.rtuMin.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMin*COM_RATE_CUR; it.rtuAlarmMin.append(rtuCmd);

        //        snmpCmd.oid = QString("%1.%2.%3.1.12.%4.0").arg(MIB_OID_CLEVER).arg(R_MIB_OID).arg(addr).arg(i+1);
        //        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMax).toUtf8(); it.sAlarmMax.append(snmpCmd);
        //        snmpCmd.value = QString("%1.0").arg(Test_Normal_OutputCurMax).toUtf8();  it.sMax.push_front(snmpCmd);

        rtuCmd.reg = R_RtuReg_OutputCurMax+i;
        rtuCmd.value = Test_Abnormal_CurMax*COM_RATE_CUR; it.rtuMax.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMax*COM_RATE_CUR; it.rtuAlarmMax.append(rtuCmd);
    }

    return true;
}


bool RTest_CoreThread::outputSwCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;

    for(int i=0; i<it.num; ++i) {
        snmpCmd.oid = QString("%1.%2.%3.1.9.%4.0").arg(MIB_OID_CLEVER).arg(R_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = "OFF"; it.sAlarmMin.append(snmpCmd);

        rtuCmd.reg = R_RtuReg_OutputSw+i;
        rtuCmd.value = 1; it.rtuMin.append(rtuCmd);
        snmpCmd.oid = QString("%1.%2.%3.1.9.%4.0").arg(MIB_OID_CLEVER).arg(R_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = "ON"; it.sAlarmMax.append(snmpCmd);
    }

    return true;
}

void RTest_CoreThread::outputCloseSwCmd(sTestSetCmd &it)
{
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    snmpCmd.type = SNMP_STRING_TYPE;

    for(int i = 0; i < it.num; ++i) {
        snmpCmd.oid = QString("%1.%2.%3.1.9.%4.0").arg(MIB_OID_CLEVER).arg(R_MIB_OID).arg(addr).arg(i+1);
        if(i != 0 )
            snmpCmd.value = "OFF";
        else
            snmpCmd.value = "ON";
        it.sAlarmMin.append(snmpCmd);
    }

}

void RTest_CoreThread::outputCloseAndOpenIndexSwCmd(sTestSetCmd &it,int index)
{
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    snmpCmd.type = SNMP_STRING_TYPE;

    if(!it.sAlarmMin.isEmpty()){
        it.sAlarmMin.clear();
    }

    snmpCmd.oid = QString("%1.%2.%3.1.9.%4.0").arg(MIB_OID_CLEVER).arg(R_MIB_OID).arg(addr).arg(index);
    snmpCmd.value = "OFF"; it.sAlarmMin.append(snmpCmd);

    snmpCmd.oid = QString("%1.%2.%3.1.9.%4.0").arg(MIB_OID_CLEVER).arg(R_MIB_OID).arg(addr).arg(index+1);
    snmpCmd.value = "ON"; it.sAlarmMin.append(snmpCmd);
}

bool RTest_CoreThread::outputEleCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;

    for(int i=0; i<it.num; ++i) {
        rtuCmd.reg = R_RtuReg_OutputEle+i;
        rtuCmd.value = 0; it.rtuMin.append(rtuCmd);
    }

    return true;
}

bool RTest_CoreThread::lineEleCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;

    for(int i=0; i<it.num; ++i) {
        rtuCmd.reg = R_RtuReg_LineEle+i;
        rtuCmd.value = 0; it.rtuMin.append(rtuCmd);
    }

    return true;
}

bool RTest_CoreThread::temHumCmd(sTestSetCmd &it)
{
    //temCmd(it);
    //humCmd(it);

    return true;
}

void RTest_CoreThread::temCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;
    for(int i=0; i<it.num; ++i) {

    }
}

void RTest_CoreThread::humCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;
    for(int i=0; i<it.num; ++i) {

    }
}

bool RTest_CoreThread::clearEleCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    rtuCmd.addr  = it.devId;
    //    rtuCmd.reg = R_RtuReg_ClearEle;
    //    rtuCmd.value = 0; it.rtuMin.append(rtuCmd);
    return true;
}

bool RTest_CoreThread::setFactoryCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    rtuCmd.addr  = it.devId;
    return true;
}

