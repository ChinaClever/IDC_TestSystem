#ifndef MV1_DBLINERECORDS_H
#define MV1_DBLINERECORDS_H
#include "sqlcom/dblinerecords.h"

#define MV1_DB_RealRecords "mv1_line_records"

class MV1_DbLineRecords : public DbLineRecords
{
    MV1_DbLineRecords();
public:
    static MV1_DbLineRecords *bulid();
    virtual QString tableName(){return QString("%1").arg(MV1_DB_RealRecords) ;}
};

#endif // MV1_DBLINERECORDS_H
