#ifndef IP_DPALARMSLAVE_H
#define IP_DPALARMSLAVE_H

#include "ip_dpslavetrans.h"

class IP_DpAlarmSlave : public IP_DpSlaveRecord
{
    Q_OBJECT
public:
    explicit IP_DpAlarmSlave(QObject *parent = nullptr);

protected:
    void saveMsg(int id, int line, const QString &typeStr, const QString &str);
    void unitAlarm(int id, int line, const QString &str, IP_sDataUnit &unit, double rate, const QString &sym);
    void saveLogItem(int id);
    void alarmDataUnit(int line, IP_sDataUnit &unit);
};

#endif // IP_DPALARMSLAVE_H
