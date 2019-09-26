/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "rtest_corethread.h"
#include "r_snmp/r_snmptrans.h"
#include "r_rtu/r_rturegenum.h"

RTest_CoreThread::RTest_CoreThread(QObject *parent) : TestCoreThread(parent)
{

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

