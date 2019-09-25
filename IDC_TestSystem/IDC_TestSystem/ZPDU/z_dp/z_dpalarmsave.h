#ifndef Z_DPALARMSAVE_H
#define Z_DPALARMSAVE_H

#include "dpcom/dpalarmsave.h"
#include "z_sql/z_dbalarm.h"

class Z_DpAlarmSave : public DpAlarmSave
{
    Q_OBJECT
public:
    explicit Z_DpAlarmSave(QObject *parent = nullptr);

protected:
    void insertItem(DbAlarmItem &item){Z_DbAlarm::bulid()->insertItem(item);}
};

#endif // Z_DPALARMSAVE_H
