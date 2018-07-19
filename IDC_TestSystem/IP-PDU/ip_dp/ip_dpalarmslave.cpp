#include "ip_dpalarmslave.h"
#include "ip_sql/ipdbalarm.h"


IP_DpAlarmSlave::IP_DpAlarmSlave(QObject *parent) : IP_DpSlaveRecord(parent)
{

}


/**
 * @brief 保存日志
 * @param id
 * @param line
 * @param typeStr
 * @param str
 */
void IP_DpAlarmSlave::saveMsg(int id, int line, const QString &typeStr, const QString &str)
{
    IpDbAlarmItem item;
    item.dev_id = id+1;
    item.line = line+1;
    item.type_str = typeStr;
    item.msg = str;
    IpDbAlarm::bulid()->insertItem(item);
    msleep(15);
}


void IP_DpAlarmSlave::alarmDataUnit(int line, IP_sDataUnit &unit)
{
    int i = line;
    if((unit.value[i] < unit.min[i]) || (unit.value[i] > unit.max[i]))
    {
        if(unit.alarm[i] == 0)
            unit.alarm[i] = 1;
    } else {
        unit.alarm[i] = 0;
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
void IP_DpAlarmSlave::unitAlarm(int id, int line, const QString &str, IP_sDataUnit &unit, double rate, const QString &sym)
{
    QString typeStr = str + tr("报警");
    if(line > 3) {  qDebug() << "IP_AlarmLogThread unitAlarm line err" << line ;  return; }
    for(int i=0; i<line; ++i)
    {
        alarmDataUnit(i, unit);
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
void IP_DpAlarmSlave::saveLogItem(int id)
{
    IpDevPacket *packet = IpDataPackets::bulid()->getDev(id);
    IP_RtuRecvLine *dev = &(packet->rtuData.data);

    int line = dev->lineNum;
    unitAlarm(id, line, tr("电流"), dev->cur, COM_RATE_CUR, "A");
    unitAlarm(id, line, tr("电压"), dev->vol, COM_RATE_VOL, "V");
    unitAlarm(id, 1, tr("温度"), dev->tem, COM_RATE_TEM, " ℃");
    unitAlarm(id, 1, tr("湿度"), dev->hum, COM_RATE_HUM, " %");
}
