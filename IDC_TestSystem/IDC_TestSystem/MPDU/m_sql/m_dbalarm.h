#ifndef M_DBALARM_H
#define M_DBALARM_H
#include "sqlcom/dbalarm.h"

#define M_DB_Alarms "m_dev_alarms"

class M_DbAlarm : public DbAlarm
{
    M_DbAlarm();
public:
    static M_DbAlarm *bulid();
    virtual QString tableName(){return QString("%1").arg(M_DB_Alarms);}
};

#endif // M_DBALARM_H
