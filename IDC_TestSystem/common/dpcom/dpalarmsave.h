#ifndef DPALARMSLAVE_H
#define DPALARMSLAVE_H

#include "dpsaverecord.h"

class DpAlarmSave : public DpSaveRecord
{
    Q_OBJECT
public:
    explicit DpAlarmSave(QObject *parent = nullptr);

protected:
    void saveMsg(int id, int line, const QString &typeStr, const QString &str);
    void unitAlarm(int id, int line, const QString &str, sDataUnit &unit, double rate, const QString &sym);
    void saveLogItem(int id);
    void alarmDataUnit(sDataUnit &unit);

    virtual void insertItem(DbAlarmItem &item)=0;
};

#endif // DPALARMSLAVE_H
