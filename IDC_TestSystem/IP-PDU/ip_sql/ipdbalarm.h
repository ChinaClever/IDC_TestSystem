#ifndef IPDBALARM_H
#define IPDBALARM_H
#include "si_sql/sidbalarm.h"

#define IP_DB_Alarms "ip_dev_alarms"
typedef SiDbAlarmItem IpDbAlarmItem;

class IpDbAlarm : public SiDbAlarm
{
    IpDbAlarm();
public:
    static IpDbAlarm *bulid();
    virtual QString tableName(){return QString("%1").arg(IP_DB_Alarms);}
};

#endif // IPDBALARM_H
