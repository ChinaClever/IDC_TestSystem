#ifndef MV1_DPALARMSLAVE_H
#define MV1_DPALARMSLAVE_H
#include "dpcom/dpalarmsave.h"
#include "mv1_sql/mv1_dbalarm.h"

class MV1_DpAlarmSave : public DpAlarmSave
{
    Q_OBJECT
public:
    explicit MV1_DpAlarmSave(QObject *parent = nullptr);

protected:
    void insertItem(DbAlarmItem &item){MV1_DbAlarm::bulid()->insertItem(item);}
};

#endif // MV1_DPALARMSLAVE_H
