#ifndef IPDBREALRECORDS_H
#define IPDBREALRECORDS_H
#include "sqlcom/dblinerecords.h"

#define IP_DB_RealRecords "ip_line_records"

class IpDbRealRecords : public DbLineRecords
{
    IpDbRealRecords();
public:
    static IpDbRealRecords *bulid();
    virtual QString tableName(){return QString("%1").arg(IP_DB_RealRecords) ;}
};

#endif // IPDBREALRECORDS_H
