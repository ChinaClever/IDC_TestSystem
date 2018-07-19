#ifndef IPDBTHRESHOLDS_H
#define IPDBTHRESHOLDS_H
#include "si_sql/sidbthresholds.h"

#define IP_DB_Thresholds "ip_dev_thresholds"
typedef SiDbThresholdItem IpDbThresholdItem;

class IpDbThresholds : public SiDbThresholds
{
    IpDbThresholds();
public:
    static IpDbThresholds *bulid();
    virtual QString tableName(){return QString("%1").arg(IP_DB_Thresholds) ;}
};

#endif // IPDBTHRESHOLDS_H
