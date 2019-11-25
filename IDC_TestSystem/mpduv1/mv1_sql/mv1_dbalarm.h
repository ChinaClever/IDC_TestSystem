#ifndef MV1_DBALARM_H
#define MV1_DBALARM_H
#include "sqlcom/dbalarm.h"

#define MV1_DB_Alarms "mv1_dev_alarms"

class MV1_DbAlarm : public DbAlarm
{
    MV1_DbAlarm();
public:
    static MV1_DbAlarm *bulid();
    virtual QString tableName(){return QString("%1").arg(MV1_DB_Alarms);}
};

#endif // MV1_DBALARM_H
