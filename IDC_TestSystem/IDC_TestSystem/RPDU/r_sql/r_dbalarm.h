#ifndef R_DBALARZ_H
#define R_DBALARZ_H
#include "sqlcom/dbalarm.h"

#define R_DB_Alarms "r_dev_alarms"

class R_DbAlarm : public DbAlarm
{
    R_DbAlarm();
public:
    static R_DbAlarm *bulid();
    virtual QString tableName(){return QString("%1").arg(R_DB_Alarms);}
};

#endif // R_DBALARZ_H
