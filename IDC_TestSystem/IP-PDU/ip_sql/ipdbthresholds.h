#ifndef IPDBTHRESHOLDS_H
#define IPDBTHRESHOLDS_H
#include "sqlcom/dblinethresholds.h"

#define IP_DB_Thresholds "ip_line_thresholds"

class IpDbThresholds : public DbLineThresholds
{
    IpDbThresholds();
public:
    static IpDbThresholds *bulid();
    virtual QString tableName(){return QString("%1").arg(IP_DB_Thresholds) ;}
};

#endif // IPDBTHRESHOLDS_H
