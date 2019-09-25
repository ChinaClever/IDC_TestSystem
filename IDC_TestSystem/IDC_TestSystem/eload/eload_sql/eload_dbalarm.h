#ifndef ELOAD_DBALARM_H
#define ELOAD_DBALARM_H
#include "sqlcom/dbalarm.h"

#define ELoad_DB_Alarms "eload_dev_alarms"

class ELoad_DbAlarm : public DbAlarm
{
    ELoad_DbAlarm();
public:
    static ELoad_DbAlarm *bulid();
    virtual QString tableName(){return QString("%1").arg(ELoad_DB_Alarms);}
};

#endif // ELOAD_DBALARM_H
