#ifndef IP_DPSAVETHRESHOLD_H
#define IP_DPSAVETHRESHOLD_H

#include "ip_dpslaverecord.h"
#include "ip_sql/ipdbthresholds.h"
#include "dpcom/dpsavelinethreshold.h"

class IP_DpSaveThreshold : public DpSaveLineThreshold
{
    Q_OBJECT
public:
    explicit IP_DpSaveThreshold(QObject *parent = nullptr);

protected:
    void insertItem(DbLineThresholdItem &item){IpDbThresholds::bulid()->insertItem(item);}
};

#endif // IP_DPSAVETHRESHOLD_H
