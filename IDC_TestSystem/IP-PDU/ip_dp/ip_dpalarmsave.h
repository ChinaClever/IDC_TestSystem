#ifndef IP_DPALARMSLAVE_H
#define IP_DPALARMSLAVE_H
#include "ip_dpsavetrans.h"
#include "dpcom/dpalarmsave.h"
#include "ip_sql/ipdbalarm.h"

class IP_DpAlarmSave : public DpAlarmSave
{
    Q_OBJECT
public:
    explicit IP_DpAlarmSave(QObject *parent = nullptr);

protected:
    void insertItem(DbAlarmItem &item){IpDbAlarm::bulid()->insertItem(item);}
};

#endif // IP_DPALARMSLAVE_H
