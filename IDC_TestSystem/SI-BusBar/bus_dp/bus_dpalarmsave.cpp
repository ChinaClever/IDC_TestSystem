/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_dpalarmsave.h"
#include "bus_sql/busdbalarm.h"

static QMutex mutex; // 互拆锁
static QStringList gAlarmStr; // 实时告警内容 存储格式 母线名称，告警类型，告警内容

/**
 * @brief 获取实时告警内容
 * @return  实时告警内容 存储格式 母线名称，告警类型，告警内容
 */
QStringList get_alarm_str()
{
    QMutexLocker locker(&mutex);
    QStringList str = gAlarmStr;
    gAlarmStr.clear();

    return str;
}



BUS_DpAlarmSave::BUS_DpAlarmSave(QObject *parent) : QThread(parent)
{
    isRun = false;
}


void BUS_DpAlarmSave::saveMsg(QStringList &list, const QString &typeStr, const QString &str)
{
    BusDbAlarmItem item;
    item.bus = list.at(0);
    item.box = list.at(1);
    item.loop = list.at(2);
    item.type_str = typeStr;
    item.msg = str;

    BusDbAlarm::bulid()->insertItem(item);
    msleep(15);
}


void BUS_DpAlarmSave::unitAlarm(QStringList &list, QString &typeStr, BUS_sDataUnit &unit,double rate, const QString &sym)
{
    QString str, tempStr = typeStr;
    if(unit.alarm)
    {
        tempStr = typeStr + QObject::tr("告警");
        str += QObject::tr("%1当前值：%2%3, 最小值：%4%5, 最大值：%6%7").arg(" ")
                .arg(unit.value/rate).arg(sym)
                .arg(unit.min/rate).arg(sym)
                .arg(unit.max/rate).arg(sym);

        if(unit.alarm == 1){
            unit.alarm = 2;
            saveMsg(list, typeStr, str);
        }
    }
    else if(unit.crAlarm)
    {
        tempStr = typeStr +  QObject::tr("预警");
        str += QObject::tr("%1当前值：%2%3, 临界下限值：%4%5, 临界上限值：%6%7").arg(" ")
                .arg(unit.value/rate).arg(sym)
                .arg(unit.crMin/rate).arg(sym)
                .arg(unit.crMax/rate).arg(sym);
    }

    // 实时告警信息
    if((unit.alarm) || (unit.crAlarm)) {
        mAlarmStr << list;
        mAlarmStr << tempStr;
        mAlarmStr << str;
    }
}


void BUS_DpAlarmSave::boxAlarm(int busId, int boxId)
{
    QString busName = BusPacketSi::bulid()->getBusName(busId);
    sBoxData *box =  BusPacketSi::bulid()->getBox(busId, boxId);

    for(int i=0; i<box->loopNum; ++i)
    {
        QStringList list;
        list << busName << box->name << box->loop[i].name;

        QString typeStr = QObject::tr("电流");
        unitAlarm(list, typeStr, box->loop[i].cur, COM_RATE_CUR, "A");

        typeStr = QObject::tr("电压");
        unitAlarm(list, typeStr, box->loop[i].vol, COM_RATE_VOL, "V");

        typeStr = QObject::tr("温度");
        list[2] = QObject::tr("温度").arg(i+1);
        unitAlarm(list, typeStr, box->env[i].tem, COM_RATE_TEM, "°C");
    }
}


void BUS_DpAlarmSave::busAlarm(int id)
{
    sBusData *bus =  BusPacketSi::bulid()->getBus(id);
    for(int i=0; i<=bus->boxNum; ++i) {
        boxAlarm(id, i);
    }
}


void BUS_DpAlarmSave::checkAlarm()
{
    for(int i=0; i<BUS_NUM; ++i)
        busAlarm(i);

    QMutexLocker locker(&mutex);
    gAlarmStr = mAlarmStr;
    mAlarmStr.clear();
}


void BUS_DpAlarmSave::run()
{
    if(isRun == false)
    {
        isRun  = true;
        checkAlarm();
        isRun  = false;
    }
}

