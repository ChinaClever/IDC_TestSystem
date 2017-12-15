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
    SiDbAlarmItem item;
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
void SI_AlarmLogThread::unitAlarm(int id, int line, const QString &str, SI_sDataUnit &unit, double rate, const QString &sym)
{
    QString typeStr = str + tr("报警");
    for(int i=0; i<line; ++i)
    {
        if(unit.alarm[i] == 1)
        {
             QString msg = tr("%1当前值：%2%3, 最小值：%4%5, 最大值：%6%7").arg(" ")
                    .arg(unit.value[i]/rate).arg(sym)
                    .arg(unit.min[i]/rate).arg(sym)
                    .arg(unit.max[i]/rate).arg(sym);

            saveMsg(id, i, typeStr, msg);
            unit.alarm[i] = 2;
        }
    }
}

/**
 * @brief 保存日志
 * @param id
 */
void SI_AlarmLogThread::saveAlarm(int id)
{
    SiDevPacket *packet = SIDataPackets::bulid()->getDev(id);
    SI_RtuRecvLine *dev = &(packet->rtuData.data);

    int line = dev->lineNum;
    unitAlarm(id, line, tr("电流"), dev->cur, COM_RATE_CUR, "A");
    unitAlarm(id, line, tr("电压"), dev->vol, COM_RATE_VOL, "V");
    unitAlarm(id, 1, tr("温度"), dev->tem, COM_RATE_TEM, " ℃");
    unitAlarm(id, 1, tr("湿度"), dev->hum, COM_RATE_HUM, " %");
}
