#ifndef R_DPALARMSAVE_H
#define R_DPALARMSAVE_H

#include "dpcom/dpalarmsave.h"
#include "r_sql/r_dbalarm.h"

class R_DpAlarmSave : public DpAlarmSave
{
    Q_OBJECT
public:
    explicit R_DpAlarmSave(QObject *parent = nullptr);

protected:
    void insertItem(DbAlarmItem &item){R_DbAlarm::bulid()->insertItem(item);}
};

#endif // R_DPALARMSAVE_H
