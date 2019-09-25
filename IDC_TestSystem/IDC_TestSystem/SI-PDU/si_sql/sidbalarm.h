#ifndef SIDBALARM_H
#define SIDBALARM_H
#include "sqlcom/dbalarm.h"

#define SI_DB_Alarms "si_dev_alarms"

class SiDbAlarm : public DbAlarm
{
    SiDbAlarm();
public:
    static SiDbAlarm *bulid();
    virtual QString tableName(){return QString("%1").arg(SI_DB_Alarms);}
};

#endif // SIDBALARM_H
