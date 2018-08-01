/*
 * Si 报警保存日志
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_alarmlogthread.h"
#include "si_sql/sidbalarm.h"

SI_AlarmLogThread::SI_AlarmLogThread(QObject *parent) : QThread(parent)
{

}

SI_AlarmLogThread *SI_AlarmLogThread::bulid()
{
    static SI_AlarmLogThread* sington = nullptr;
    if(sington == nullptr)
        sington = new SI_AlarmLogThread();
    return sington;
}

/**
 * @brief 保存日志
 * @param id
 * @param line
 * @param typeStr
 * @param str
 */
void SI_AlarmLogThread::saveMsg(int id, int line, const QString &typeStr, const QString &str)
{
    DbAlarmItem item;
    item.dev_id = id+1;
    item.line = line+1;
    item.type_str = typeStr;
    item.msg = str;
    SiDbAlarm::bulid()->insertItem(item);
    msleep(15);
}

/**
 * @brief 数据单元处理
 * @param id
 * @param str
 * @param unit
 * @param rate
 * @param sym
 */
void SI_AlarmLogThread::unitAlarm(int id, int i, const QString &str, sDataUnit &unit, double rate, const QString &sym)
{
    QString typeStr = str + tr("报警");
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
void SI_AlarmLogThread::saveAlarm(int id)
{
    sDataPacket *packet = SIDataPackets::bulid()->getDev(id);
     sDevData *data = &(packet->data);

    int line = data->lineNum;
    for(int i=0; i<line; ++i) {
        unitAlarm(id, i, tr("电流"), data->line[i].cur, COM_RATE_CUR, "A");
        unitAlarm(id, i, tr("电压"), data->line[i].vol, COM_RATE_VOL, "V");
    }

    line = data->env.envNum;
    for(int i=0; i<line; ++i) {
        unitAlarm(id, i, tr("温度"), data->env.tem[i], COM_RATE_TEM, " ℃");
        unitAlarm(id, i, tr("湿度"), data->env.hum[i], COM_RATE_HUM, " %");
    }
}
