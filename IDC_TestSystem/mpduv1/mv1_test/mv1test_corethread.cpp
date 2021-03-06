﻿#include "mv1test_corethread.h"
#include "mv1_snmp/mv1_snmptrans.h"
#include "mv1_rtu/mv1_rturegenum.h"


MV1Test_CoreThread::MV1Test_CoreThread(QObject *parent) : TestCoreThread(parent)
{

}


bool MV1Test_CoreThread::lineVolCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;

    for(int i=0; i<it.num; ++i) {
        rtuCmd.reg = 1079+i;
        rtuCmd.value = Test_Normal_VolMin; it.rtuMin.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_VolMin; it.rtuAlarmMin.append(rtuCmd);

        rtuCmd.reg = 1082+i;
        rtuCmd.value = Test_Normal_VolMax; it.rtuMax.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_VolMax; it.rtuAlarmMax.append(rtuCmd);
    }

    return true;
}

int MV1Test_CoreThread::getLoopNum()
{
    int ret = mDevPacket->data.loopNum;
    mDevPacket->data.loopNum = 0;

    return ret;
}

bool MV1Test_CoreThread::loopVolCmd(sTestSetCmd &it)
{

    return true;
}

bool MV1Test_CoreThread::lineCurCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;

    for(int i=0; i<it.num; ++i) {
        rtuCmd.reg = 1205+i;
        rtuCmd.value = Test_Normal_CurMin; it.rtuMin.push_front(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMin; it.rtuAlarmMin.append(rtuCmd);
        rtuCmd.reg = 1085+i;
        rtuCmd.value = Test_Normal_CurMin; it.rtuMin.push_front(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMin; it.rtuAlarmMin.append(rtuCmd);

        rtuCmd.reg = 1208+i;
        rtuCmd.value = Test_Normal_LineCurMax; it.rtuMax.push_front(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMax; it.rtuAlarmMax.append(rtuCmd);
        rtuCmd.reg = 1088+i;
        rtuCmd.value = Test_Normal_LineCurMax; it.rtuMax.push_front(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMax; it.rtuAlarmMax.append(rtuCmd);
    }

    return true;
}


bool MV1Test_CoreThread::loopCurCmd(sTestSetCmd &it)
{
    return true;
}


bool MV1Test_CoreThread::outputCurCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;

    for(int i=0; i<it.num; ++i) {

        rtuCmd.reg = 1123+i;
        rtuCmd.value = Test_Normal_CurMin; it.rtuMin.push_front(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMin; it.rtuAlarmMin.append(rtuCmd);
        rtuCmd.reg = 1099+i;
        rtuCmd.value = Test_Normal_CurMin; it.rtuMin.push_front(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMin; it.rtuAlarmMin.append(rtuCmd);

        rtuCmd.reg = 1181+i;
        rtuCmd.value = Test_Abnormal_CurMax; it.rtuMax.push_front(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMax; it.rtuAlarmMax.append(rtuCmd);
        //rtuCmd.reg = 1147+i;
        //rtuCmd.value = Test_Abnormal_CurMax; it.rtuMax.push_front(rtuCmd);
        //rtuCmd.value = Test_Abnormal_CurMax; it.rtuAlarmMax.append(rtuCmd);
    }

    return true;
}


bool MV1Test_CoreThread::outputSwCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    switch(addr)
    {
    case 1:addr = 8;break;
    case 2:addr = 15;break;
    case 3:addr = 22;break;
    case 4:addr = 29;break;
    default: addr = 8;break;
    }
    snmpCmd.type = SNMP_STRING_TYPE;
    for(int i=0; i<it.num; ++i) {
        snmpCmd.oid = QString("%1.%2.%3.%4.0").arg(MIB_OID_CLEVER).arg(MV1_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = "OFF"; it.sAlarmMin.append(snmpCmd);

        rtuCmd.reg = 1003+i;
        rtuCmd.value = 1; it.rtuMin.append(rtuCmd);
        snmpCmd.oid = QString("%1.%2.%3.%4.0").arg(MIB_OID_CLEVER).arg(MV1_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = "ON"; it.sAlarmMax.append(snmpCmd);
    }

    return true;
}

void MV1Test_CoreThread::outputCloseSwCmd(sTestSetCmd &it)
{
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    snmpCmd.type = SNMP_STRING_TYPE;

    switch(addr)
    {
    case 1:addr = 8;break;
    case 2:addr = 15;break;
    case 3:addr = 22;break;
    case 4:addr = 29;break;
    default: addr = 8;break;
    }
    for(int i = 0; i < it.num; ++i) {
        snmpCmd.oid = QString("%1.%2.%3.%4.0").arg(MIB_OID_CLEVER).arg(MV1_MIB_OID).arg(addr).arg(i+1);
        if(i != 0 )
            snmpCmd.value = "OFF";
        else
            snmpCmd.value = "ON";
        it.sAlarmMin.append(snmpCmd);
    }
}

void MV1Test_CoreThread::outputCloseAndOpenIndexSwCmd(sTestSetCmd &it,int index)
{
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    snmpCmd.type = SNMP_STRING_TYPE;

    switch(addr)
    {
    case 1:addr = 8;break;
    case 2:addr = 15;break;
    case 3:addr = 22;break;
    case 4:addr = 29;break;
    default: addr = 8;break;
    }
    if(!it.sAlarmMin.isEmpty()){
        it.sAlarmMin.clear();
    }

    snmpCmd.oid = QString("%1.%2.%3.%4.0").arg(MIB_OID_CLEVER).arg(MV1_MIB_OID).arg(addr).arg(index);
    snmpCmd.value = "OFF"; it.sAlarmMin.append(snmpCmd);

    snmpCmd.oid = QString("%1.%2.%3.%4.0").arg(MIB_OID_CLEVER).arg(MV1_MIB_OID).arg(addr).arg(index+1);
    snmpCmd.value = "ON"; it.sAlarmMin.append(snmpCmd);
}

bool MV1Test_CoreThread::outputEleCmd(sTestSetCmd &it)
{//暂时不用
    sRtuSetCmd rtuCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;

    for(int i=0; i<it.num; ++i) {
        rtuCmd.reg = 1030+i;
        rtuCmd.value = 0; it.rtuMin.append(rtuCmd);
    }

    return true;
}

bool MV1Test_CoreThread::lineEleCmd(sTestSetCmd &it)
{//暂时不用
    sRtuSetCmd rtuCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;

    for(int i=0; i<it.num; ++i) {
        rtuCmd.value = 0; it.rtuMin.append(rtuCmd);
    }

    return true;
}

bool MV1Test_CoreThread::temHumCmd(sTestSetCmd &it)
{//暂时不用
    temCmd(it);
    humCmd(it);

    return true;
}

void MV1Test_CoreThread::temCmd(sTestSetCmd &it)
{//暂时不用
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;
    for(int i=0; i<it.num; ++i) {
        rtuCmd.reg = ZM_RtuReg_TemMin+i;
        rtuCmd.value = Test_Normal_TemMin; it.rtuMin.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_TemMin; it.rtuAlarmMin.append(rtuCmd);

        rtuCmd.reg = ZM_RtuReg_TemMax+i;
        rtuCmd.value = Test_Normal_TemMax; it.rtuMax.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_TemMax; it.rtuAlarmMax.append(rtuCmd);
    }
}

void MV1Test_CoreThread::humCmd(sTestSetCmd &it)
{//暂时不用
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;
    for(int i=0; i<it.num; ++i) {       
        rtuCmd.reg = ZM_RtuReg_HumMin+i;
        rtuCmd.value = Test_Normal_HumMin; it.rtuMin.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_HumMin; it.rtuAlarmMin.append(rtuCmd);

        rtuCmd.reg = ZM_RtuReg_HumMax+i;
        rtuCmd.value = Test_Normal_HumMax; it.rtuMax.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_HumMax; it.rtuAlarmMax.append(rtuCmd);
    }
}

bool MV1Test_CoreThread::clearEleCmd(sTestSetCmd &it)
{//暂时不用
    sRtuSetCmd rtuCmd;
    rtuCmd.addr  = it.devId;
    rtuCmd.reg = ZM_RtuReg_ClearEle;
    rtuCmd.value = 0; it.rtuMin.append(rtuCmd);
    return true;
}

bool MV1Test_CoreThread::setFactoryCmd(sTestSetCmd &it)
{//暂时不用
    sRtuSetCmd rtuCmd;
    rtuCmd.addr  = it.devId;
    rtuCmd.reg = ZM_RtuReg_SetFactory;
    rtuCmd.value = 0; it.rtuMin.append(rtuCmd);
    return true;
}

int MV1Test_CoreThread::getLoopPorts()
{
    return 0;
}

bool MV1Test_CoreThread::curAcc(int expect, int measured, sTestDataItem &item, double f)
{
    bool ret = false;
    int value = f>10?expect/COM_RATE_CUR - measured*mRate:expect- measured*mRate;
    item.expect = QString::number(f>10?expect/COM_RATE_CUR2:expect/COM_RATE_CUR) + "A";

    int min = -8*COM_RATE_VOL;
    int max =  8*COM_RATE_VOL;
    if( expect != 0 && measured != 0 ) {
        if((value > min) && (value < max)) {
            ret = true;
        }
    }

    return ret;
}
