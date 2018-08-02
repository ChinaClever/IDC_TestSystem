#ifndef SI_DPALARMSLAVE_H
#define SI_DPALARMSLAVE_H
#include "si_com/sidatapackets.h"
#include "dpcom/dpalarmsave.h"
#include "si_sql/sidbalarm.h"

class SI_DpAlarmSave : public DpAlarmSave
{
    Q_OBJECT
public:
    explicit SI_DpAlarmSave(QObject *parent = nullptr);

protected:
    void insertItem(DbAlarmItem &item){SiDbAlarm::bulid()->insertItem(item);}
};

#endif // SI_DPALARMSLAVE_H
