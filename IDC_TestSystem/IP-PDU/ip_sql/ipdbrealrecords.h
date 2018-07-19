#ifndef IPDBREALRECORDS_H
#define IPDBREALRECORDS_H
#include "si_sql/sidbrealrecords.h"

#define IP_DB_RealRecords "ip_real_records"
typedef SiDbRealRecordItem IpDbRealRecordItem;

class IpDbRealRecords : public SiDbRealRecords
{
    IpDbRealRecords();
public:
    static IpDbRealRecords *bulid();
    virtual QString tableName(){return QString("%1").arg(IP_DB_RealRecords) ;}
};

#endif // IPDBREALRECORDS_H
