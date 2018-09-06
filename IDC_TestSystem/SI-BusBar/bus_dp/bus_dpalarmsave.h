#ifndef BUS_DPALARMSLAVE_H
#define BUS_DPALARMSLAVE_H
#include "bus_dpalarm.h"
#include "bus_com/buspacketsi.h"

class BUS_DpAlarmSave : public QThread
{
public:
    BUS_DpAlarmSave(QObject *parent = nullptr);
    void run();

protected:
    void unitAlarm(QStringList &list, QString &typeStr, sDataUnit &unit, double rate, const QString &sym);

    void boxAlarm(int busId, int boxId);
    void busAlarm(int id);
    void checkAlarm();

   void saveMsg(QStringList &list, const QString &typeStr, const QString &str);

private:
    QStringList mAlarmStr;
    bool isRun;
};

#endif // BUS_DPALARMSLAVE_H
