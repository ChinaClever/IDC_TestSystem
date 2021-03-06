﻿#include "mtest_corethread.h"
#include "m_snmp/m_snmptrans.h"
#include "m_rtu/m_rturegenum.h"


MTest_CoreThread::MTest_CoreThread(QObject *parent) : TestCoreThread(parent)
{

}


bool MTest_CoreThread::lineVolCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;

    for(int i=0; i<it.num; ++i) {
//        snmpCmd.oid = QString("%1.%2.%3.2.%4.10.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
//        snmpCmd.value = QString::number(Test_Normal_VolMin).toUtf8();  it.sMin.append(snmpCmd);
//        snmpCmd.value = QString::number(Test_Abnormal_VolMin).toUtf8(); it.sAlarmMin.append(snmpCmd);

        rtuCmd.reg = ZM_RtuReg_LineVolMin+i;
        rtuCmd.value = Test_Normal_VolMin; it.rtuMin.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_VolMin; it.rtuAlarmMin.append(rtuCmd);

//        snmpCmd.oid = QString("%1.%2.%3.2.%4.13.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
//        snmpCmd.value = QString::number(Test_Normal_VolMax).toUtf8();  it.sMax.append(snmpCmd);
//        snmpCmd.value = QString::number(Test_Abnormal_VolMax).toUtf8(); it.sAlarmMax.append(snmpCmd);

        rtuCmd.reg = ZM_RtuReg_LineVolMax+i;
        rtuCmd.value = Test_Normal_VolMax; it.rtuMax.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_VolMax; it.rtuAlarmMax.append(rtuCmd);
    }

    return true;
}

bool MTest_CoreThread::loopVolCmd(sTestSetCmd &it)
{

    return true;
}

bool MTest_CoreThread::lineCurCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;

    for(int i=0; i<it.num; ++i) {
        snmpCmd.oid = QString("%1.%2.%3.2.%4.7.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMin).toUtf8(); it.sAlarmMin.append(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_CurMin).toUtf8();  it.sMin.push_front(snmpCmd);

        snmpCmd.oid = QString("%1.%2.%3.2.%4.6.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMin).toUtf8(); it.sAlarmMin.append(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_CurMin).toUtf8();  it.sMin.push_front(snmpCmd);

        rtuCmd.reg = ZM_RtuReg_LineCurMin+i;
        rtuCmd.value = Test_Normal_CurMin; it.rtuMin.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMin; it.rtuAlarmMin.append(rtuCmd);
        rtuCmd.reg = ZM_RtuReg_LineCurCrMin+i;
        rtuCmd.value = Test_Normal_CurMin; it.rtuMin.append(rtuCmd);

        snmpCmd.oid = QString("%1.%2.%3.2.%4.8.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMax).toUtf8(); it.sAlarmMax.append(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_LineCurMax).toUtf8();  it.sMax.push_front(snmpCmd);
        snmpCmd.oid = QString("%1.%2.%3.2.%4.9.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMax).toUtf8(); it.sAlarmMax.append(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_LineCurMax).toUtf8();  it.sMax.push_front(snmpCmd);

        rtuCmd.reg = ZM_RtuReg_LineCurMax+i;
        rtuCmd.value = Test_Normal_LineCurMax; it.rtuMax.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMax; it.rtuAlarmMax.append(rtuCmd);
        rtuCmd.reg = ZM_RtuReg_LineCurCrMax+i;
        rtuCmd.value = Test_Normal_LineCurMax; it.rtuMax.append(rtuCmd);
    }

    return true;
}


bool MTest_CoreThread::loopCurCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;

    for(int i=0; i<it.num; ++i) {
        snmpCmd.oid = QString("%1.%2.%3.3.%4.8.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMin).toUtf8(); it.sAlarmMin.append(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_CurMin).toUtf8();  it.sMin.push_front(snmpCmd);

        snmpCmd.oid = QString("%1.%2.%3.3.%4.7.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMin).toUtf8(); it.sAlarmMin.append(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_CurMin).toUtf8();  it.sMin.push_front(snmpCmd);

        rtuCmd.reg = ZM_RtuReg_LoopCurMin+i;
        rtuCmd.value = Test_Normal_CurMin; it.rtuMin.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMin; it.rtuAlarmMin.append(rtuCmd);
        rtuCmd.reg = ZM_RtuReg_LoopCurCrMin+i;
        rtuCmd.value = Test_Normal_CurMin; it.rtuMin.append(rtuCmd);

        snmpCmd.oid = QString("%1.%2.%3.3.%4.9.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMax).toUtf8(); it.sAlarmMax.append(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_LineCurMax).toUtf8();  it.sMax.push_front(snmpCmd);
        snmpCmd.oid = QString("%1.%2.%3.3.%4.10.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMax).toUtf8(); it.sAlarmMax.append(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_LineCurMax).toUtf8();  it.sMax.push_front(snmpCmd);

        rtuCmd.reg = ZM_RtuReg_LoopCurMax+i;
        rtuCmd.value = Test_Normal_LineCurMax; it.rtuMax.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMax; it.rtuAlarmMax.append(rtuCmd);
    }
    return true;
}


bool MTest_CoreThread::outputCurCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;

    for(int i=0; i<it.num; ++i) {
        snmpCmd.oid = QString("%1.%2.%3.8.3.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMin).toUtf8(); it.sAlarmMin.append(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_CurMin).toUtf8();  it.sMin.push_front(snmpCmd);
        snmpCmd.oid = QString("%1.%2.%3.8.2.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMin).toUtf8(); it.sAlarmMin.append(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_CurMin).toUtf8();  it.sMin.push_front(snmpCmd);


//        rtuCmd.reg = ZM_RtuReg_OutputCurCrMin+i;
//        rtuCmd.value = Test_Normal_CurMin; it.rtuMin.push_front(rtuCmd);
//        rtuCmd.value = Test_Abnormal_CurMin; it.rtuAlarmMin.append(rtuCmd);
//        rtuCmd.reg = ZM_RtuReg_OutputCurMin+i;
//        rtuCmd.value = Test_Normal_CurMin; it.rtuMin.push_front(rtuCmd);
//        rtuCmd.value = Test_Abnormal_CurMin; it.rtuAlarmMin.append(rtuCmd);1

        snmpCmd.oid = QString("%1.%2.%3.8.4.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMax).toUtf8(); it.sAlarmMax.append(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMax).toUtf8();  it.sMax.push_front(snmpCmd);
        snmpCmd.oid = QString("%1.%2.%3.8.5.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMax).toUtf8(); it.sAlarmMax.append(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_CurMax).toUtf8();  it.sMax.push_front(snmpCmd);

//        rtuCmd.reg = ZM_RtuReg_OutputCurMax+i;
//        rtuCmd.value = Test_Abnormal_CurMax; it.rtuMax.append(rtuCmd);
//        rtuCmd.value = Test_Abnormal_CurMax; it.rtuAlarmMax.append(rtuCmd);1

        //rtuCmd.reg = ZM_RtuReg_OutputCurCrMax+i;
        //rtuCmd.value = Test_Abnormal_CurMax; it.rtuMax.append(rtuCmd);
    }

    return true;
}


bool MTest_CoreThread::outputSwCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;

    for(int i=0; i<it.num; ++i) {
        snmpCmd.oid = QString("%1.%2.%3.7.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = "OFF"; it.sAlarmMin.append(snmpCmd);

        rtuCmd.reg = ZM_RtuReg_OutputSw+i;
        rtuCmd.value = 1; it.rtuMin.append(rtuCmd);
        snmpCmd.oid = QString("%1.%2.%3.7.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = "ON"; it.sAlarmMax.append(snmpCmd);
    }

    return true;
}

void MTest_CoreThread::outputCloseSwCmd(sTestSetCmd &it)
{
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    snmpCmd.type = SNMP_STRING_TYPE;

    for(int i = 0; i < it.num; ++i) {
        snmpCmd.oid = QString("%1.%2.%3.7.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        if(i != 0 )
            snmpCmd.value = "OFF";
        else
            snmpCmd.value = "ON";
        it.sAlarmMin.append(snmpCmd);
    }
}

void MTest_CoreThread::outputCloseAndOpenIndexSwCmd(sTestSetCmd &it,int index)
{
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    snmpCmd.type = SNMP_STRING_TYPE;

    if(!it.sAlarmMin.isEmpty()){
        it.sAlarmMin.clear();
    }

    snmpCmd.oid = QString("%1.%2.%3.7.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(index);
    snmpCmd.value = "OFF"; it.sAlarmMin.append(snmpCmd);

    snmpCmd.oid = QString("%1.%2.%3.7.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(index+1);
    snmpCmd.value = "ON"; it.sAlarmMin.append(snmpCmd);
}

bool MTest_CoreThread::outputEleCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    //sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    //snmpCmd.type = SNMP_STRING_TYPE;

    for(int i=0; i<it.num; ++i) {
//        snmpCmd.oid = QString("%1.%2.%3.10.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
//        snmpCmd.value = "0"; it.sAlarmMin.append(snmpCmd);

        rtuCmd.reg = ZM_RtuReg_OutputEle+i;
        rtuCmd.value = 0; it.rtuMin.append(rtuCmd);
    }

    return true;
}

bool MTest_CoreThread::lineEleCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    //sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    //snmpCmd.type = SNMP_STRING_TYPE;

    for(int i=0; i<it.num; ++i) {
//        snmpCmd.oid = QString("%1.%2.%3.2.%4.5.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
//        snmpCmd.value = "0"; it.sAlarmMin.append(snmpCmd);

        rtuCmd.reg = ZM_RtuReg_LineEle+i;
        rtuCmd.value = 0; it.rtuMin.append(rtuCmd);
    }

    return true;
}

bool MTest_CoreThread::temHumCmd(sTestSetCmd &it)
{
    temCmd(it);
    humCmd(it);

    return true;
}

void MTest_CoreThread::temCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;
    for(int i=0; i<it.num; ++i) {
        snmpCmd.oid = QString("%1.%2.%3.4.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(9+i*4);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_TemMin).toUtf8(); it.sAlarmMin.push_front(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_TemMin).toUtf8();  it.sMin.append(snmpCmd);
        snmpCmd.oid = QString("%1.%2.%3.4.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(10+i*4);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_TemMin).toUtf8(); it.sAlarmMin.push_front(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_TemMin).toUtf8();  it.sMin.append(snmpCmd);

        rtuCmd.reg = ZM_RtuReg_TemMin+i;
        rtuCmd.value = Test_Normal_TemMin; it.rtuMin.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_TemMin; it.rtuAlarmMin.append(rtuCmd);

        snmpCmd.oid = QString("%1.%2.%3.4.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(11+i*4);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_TemMax).toUtf8(); it.sAlarmMax.append(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_TemMax).toUtf8();  it.sMax.push_front(snmpCmd);
        snmpCmd.oid = QString("%1.%2.%3.4.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(12+i*4);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_TemMax).toUtf8(); it.sAlarmMax.append(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_TemMax).toUtf8();  it.sMax.push_front(snmpCmd);

        rtuCmd.reg = ZM_RtuReg_TemMax+i;
        rtuCmd.value = Test_Normal_TemMax; it.rtuMax.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_TemMax; it.rtuAlarmMax.append(rtuCmd);
    }
}

void MTest_CoreThread::humCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;
    for(int i=0; i<it.num; ++i) {
        snmpCmd.oid = QString("%1.%2.%3.4.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(17+i*4);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_HumMin).toUtf8(); it.sAlarmMin.push_front(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_HumMin).toUtf8();  it.sMin.append(snmpCmd);
        snmpCmd.oid = QString("%1.%2.%3.4.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(18+i*4);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_HumMin).toUtf8(); it.sAlarmMin.push_front(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_HumMin).toUtf8();  it.sMin.append(snmpCmd);

        rtuCmd.reg = ZM_RtuReg_HumMin+i;
        rtuCmd.value = Test_Normal_HumMin; it.rtuMin.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_HumMin; it.rtuAlarmMin.append(rtuCmd);

        snmpCmd.oid = QString("%1.%2.%3.4.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(19+i*4);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_HumMax).toUtf8(); it.sAlarmMax.append(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_HumMax).toUtf8();  it.sMax.push_front(snmpCmd);
        snmpCmd.oid = QString("%1.%2.%3.4.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(20+i*4);
        snmpCmd.value = QString("%1.0").arg(Test_Abnormal_HumMax).toUtf8(); it.sAlarmMax.append(snmpCmd);
        snmpCmd.value = QString("%1.0").arg(Test_Normal_HumMax).toUtf8();  it.sMax.push_front(snmpCmd);

        rtuCmd.reg = ZM_RtuReg_HumMax+i;
        rtuCmd.value = Test_Normal_HumMax; it.rtuMax.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_HumMax; it.rtuAlarmMax.append(rtuCmd);
    }
}

bool MTest_CoreThread::clearEleCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    rtuCmd.addr  = it.devId;
    rtuCmd.reg = ZM_RtuReg_ClearEle;
    rtuCmd.value = 0; it.rtuMin.append(rtuCmd);
    return true;
}

bool MTest_CoreThread::setFactoryCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    rtuCmd.addr  = it.devId;
    rtuCmd.reg = ZM_RtuReg_SetFactory;
    rtuCmd.value = 0; it.rtuMin.append(rtuCmd);
    return true;
}
