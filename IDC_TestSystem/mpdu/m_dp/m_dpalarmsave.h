#ifndef M_DPALARMSLAVE_H
#define M_DPALARMSLAVE_H
#include "dpcom/dpalarmsave.h"
#include "m_sql/m_dbalarm.h"

class M_DpAlarmSave : public DpAlarmSave
{
    Q_OBJECT
public:
    explicit M_DpAlarmSave(QObject *parent = nullptr);

protected:
    void insertItem(DbAlarmItem &item){M_DbAlarm::bulid()->insertItem(item);}
};

#endif // M_DPALARMSLAVE_H
