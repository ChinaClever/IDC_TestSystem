/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "dpalarmsave.h"
#include "sqlcom/dbalarm.h"

DpAlarmSave::DpAlarmSave(QObject *parent) : DpSaveRecord(parent)
{
}


/**
 * @brief 保存日志
 * @param id
 * @param line
 * @param typeStr
 * @param str
 */
void DpAlarmSave::saveMsg(int id, int line, const QString &typeStr, const QString &str)
{
    DbAlarmItem item;
    item.dev_id = id;
    item.line = line+1;
    item.type_str = typeStr;
    item.msg = str;

    insertItem(item);
    msleep(LOG_DELAY);
}


void DpAlarmSave::alarmDataUnit(sDataUnit &unit)
{
    if((unit.value < unit.min) || (unit.value > unit.max))
    {
        if(unit.alarm == 0)
            unit.alarm = 1;
    } else {
        unit.alarm = 0;
    }
}


/**
 * @brief 数据单元处理
 * @param id
 * @param str
 * @param unit
 * @param rate
 * @param sym
 */
void DpAlarmSave::unitAlarm(int id, int line, const QString &str, sDataUnit &unit, double rate, const QString &sym)
{
    QString typeStr = str + tr("报警");
    int i = line;

    alarmDataUnit(unit);
    if(unit.alarm == 1)
    {
        QString msg = tr("%1当前值：%2%3, 最小值：%4%5, 最大值：%6%7").arg(" ")
                .arg(unit.value/rate).arg(sym)
                .arg(unit.min/rate).arg(sym)
                .arg(unit.max/rate).arg(sym);

        saveMsg(id, i, typeStr, msg);
        unit.alarm = 2;
    }
}

/**
 * @brief 保存日志
 * @param id
 */
void DpAlarmSave::saveLogItem(int id)
{
    sDataPacket *dev = &(mPackets->dev[id]);

    int num = dev->data.lineNum;
    for(int i=0; i<num; ++i) {
        unitAlarm(id, i, tr("电流"), dev->data.line[i].cur, COM_RATE_CUR, "A");
        unitAlarm(id, i, tr("电压"), dev->data.line[i].vol, COM_RATE_VOL, "V");
    }

    num = dev->data.loopNum;
    for(int i=0; i<num; ++i) {
        unitAlarm(id, i, tr("回路电流"), dev->data.loop[i].cur, COM_RATE_CUR, "A");
    }

    num = dev->data.outputNum;
    for(int i=0; i<num; ++i) {
        unitAlarm(id, i, tr("输出位电流"), dev->data.loop[i].cur, COM_RATE_CUR, "A");
    }

    num = dev->data.env.envNum;
    for(int i=0; i<num; ++i) {
        unitAlarm(id, i, tr("温度"), dev->data.env.tem[i], COM_RATE_TEM, " ℃");
        unitAlarm(id, i, tr("湿度"), dev->data.env.hum[i], COM_RATE_HUM, " %");
    }
}
