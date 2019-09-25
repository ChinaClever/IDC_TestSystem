#ifndef ELOAD_DBLINERECORDS_H
#define ELOAD_DBLINERECORDS_H
#include "sqlcom/dblinerecords.h"

#define ELoad_DB_RealRecords "eload_line_records"

class ELoad_DbLineRecords : public DbLineRecords
{
    ELoad_DbLineRecords();
public:
    static ELoad_DbLineRecords *bulid();
    virtual QString tableName(){return QString("%1").arg(ELoad_DB_RealRecords) ;}
};

#endif // ELOAD_DBLINERECORDS_H
