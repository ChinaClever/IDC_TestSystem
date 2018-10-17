#include "mtest_corethread.h"
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
        snmpCmd.oid = QString("%1.%2.%3.2.%4.10").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString::number(Test_Normal_VolMin).toUtf8();  it.sMin.append(snmpCmd);
        snmpCmd.value = QString::number(Test_Abnormal_VolMin).toUtf8(); it.sAlarmMin.append(snmpCmd);

        rtuCmd.reg = 145+i;
        rtuCmd.value = Test_Normal_VolMin; it.rtuMin.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_VolMin; it.rtuAlarmMin.append(rtuCmd);

        snmpCmd.oid = QString("%1.%2.%3.2.%4.13").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString::number(Test_Normal_VolMax).toUtf8();  it.sMin.append(snmpCmd);
        snmpCmd.value = QString::number(Test_Abnormal_VolMax).toUtf8(); it.sAlarmMax.append(snmpCmd);

        rtuCmd.reg = 148+i;
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
        snmpCmd.oid = QString("%1.%2.%3.2.%4.6").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString::number(Test_Normal_CurMin).toUtf8();  it.sMin.append(snmpCmd);
        snmpCmd.value = QString::number(Test_Abnormal_CurMin).toUtf8(); it.sAlarmMin.append(snmpCmd);

        rtuCmd.reg = 151+i;
        rtuCmd.value = Test_Normal_CurMin; it.rtuMin.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMin; it.rtuAlarmMin.append(rtuCmd);

        snmpCmd.oid = QString("%1.%2.%3.2.%4.9").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString::number(Test_Normal_LineCurMax).toUtf8();  it.sMin.append(snmpCmd);
        snmpCmd.value = QString::number(Test_Abnormal_CurMax).toUtf8(); it.sAlarmMax.append(snmpCmd);

        rtuCmd.reg = 154+i;
        rtuCmd.value = Test_Normal_LineCurMax; it.rtuMax.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMax; it.rtuAlarmMax.append(rtuCmd);
    }

    return true;
}


bool MTest_CoreThread::loopCurCmd(sTestSetCmd &it)
{


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
        snmpCmd.oid = QString("%1.%2.%3.8.2.%4").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString::number(Test_Normal_CurMin).toUtf8();  it.sMin.append(snmpCmd);
        snmpCmd.value = QString::number(Test_Abnormal_CurMin).toUtf8(); it.sAlarmMin.append(snmpCmd);

        rtuCmd.reg = 157+i;
        rtuCmd.value = Test_Normal_CurMin; it.rtuMin.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMin; it.rtuAlarmMin.append(rtuCmd);

        snmpCmd.oid = QString("%1.%2.%3.8.5.%4").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = QString::number(Test_Normal_OutputCurMax).toUtf8();  it.sMin.append(snmpCmd);
        snmpCmd.value = QString::number(Test_Abnormal_CurMax).toUtf8(); it.sAlarmMax.append(snmpCmd);

        rtuCmd.reg = 229+i;
        rtuCmd.value = Test_Normal_OutputCurMax; it.rtuMax.append(rtuCmd);
        rtuCmd.value = Test_Abnormal_CurMax; it.rtuAlarmMax.append(rtuCmd);
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

        rtuCmd.reg = 3392+i;
        rtuCmd.value = 1; it.rtuMin.append(rtuCmd);
    }

    return true;
}

bool MTest_CoreThread::outputEleCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;

    for(int i=0; i<it.num; ++i) {
        snmpCmd.oid = QString("%1.%2.%3.10.%4.0").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = "0"; it.sAlarmMin.append(snmpCmd);

        rtuCmd.reg = 67+i;
        rtuCmd.value = 0; it.rtuMin.append(rtuCmd);
    }

    return true;
}

bool MTest_CoreThread::lineEleCmd(sTestSetCmd &it)
{
    sRtuSetCmd rtuCmd;
    sSnmpSetCmd snmpCmd;
    int addr = it.devId;
    rtuCmd.addr  = addr;
    snmpCmd.type = SNMP_STRING_TYPE;

    for(int i=0; i<it.num; ++i) {
        snmpCmd.oid = QString("%1.%2.%3.2.%4.5").arg(MIB_OID_CLEVER).arg(M_MIB_OID).arg(addr).arg(i+1);
        snmpCmd.value = "0"; it.sAlarmMin.append(snmpCmd);

        rtuCmd.reg = 10+i;
        rtuCmd.value = 0; it.rtuMin.append(rtuCmd);
    }

    return true;
}