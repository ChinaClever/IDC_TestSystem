#ifndef ELOAD_DPALARMSAVE_H
#define ELOAD_DPALARMSAVE_H

#include "dpcom/dpalarmsave.h"
#include "ELoad_sql/ELoad_dbalarm.h"

class ELoad_DpAlarmSave : public DpAlarmSave
{
    Q_OBJECT
public:
    explicit ELoad_DpAlarmSave(QObject *parent = nullptr);

protected:
    void insertItem(DbAlarmItem &item){ELoad_DbAlarm::bulid()->insertItem(item);}
};


#endif // ELOAD_DPALARMSAVE_H
