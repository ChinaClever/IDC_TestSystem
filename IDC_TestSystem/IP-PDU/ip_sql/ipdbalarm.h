#ifndef IPDBALARM_H
#define IPDBALARM_H
#include "sqlcom/dbalarm.h"

#define IP_DB_Alarms "ip_dev_alarms"

class IpDbAlarm : public DbAlarm
{
    IpDbAlarm();
public:
    static IpDbAlarm *bulid();
    virtual QString tableName(){return QString("%1").arg(IP_DB_Alarms);}
};

#endif // IPDBALARM_H
