#ifndef BUS_DPALARM_H
#define BUS_DPALARM_H

#include "bus_dptg.h"

class BUS_DpAlarm : public QObject
{
    Q_OBJECT
public:
    explicit BUS_DpAlarm(QObject *parent = nullptr);
    void alarm();

protected:
    void alarmDataUnit(BUS_sDataUnit &unit, bool cr=false);
    void boxAlarm(sBoxData &box);
    void busAlarm(sBusData *bus);
};

#endif // BUS_DPALARM_H
