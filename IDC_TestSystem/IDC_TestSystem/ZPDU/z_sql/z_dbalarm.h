#ifndef Z_DBALARZ_H
#define Z_DBALARZ_H
#include "sqlcom/dbalarm.h"

#define Z_DB_Alarms "z_dev_alarms"

class Z_DbAlarm : public DbAlarm
{
    Z_DbAlarm();
public:
    static Z_DbAlarm *bulid();
    virtual QString tableName(){return QString("%1").arg(Z_DB_Alarms);}
};

#endif // Z_DBALARZ_H
