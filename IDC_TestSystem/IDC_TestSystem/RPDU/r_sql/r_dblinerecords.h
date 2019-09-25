#ifndef R_DBLINERECORDS_H
#define R_DBLINERECORDS_H
#include "sqlcom/dblinerecords.h"

#define R_DB_RealRecords "r_line_records"

class R_DbLineRecords : public DbLineRecords
{
    R_DbLineRecords();
public:
    static R_DbLineRecords *bulid();
    virtual QString tableName(){return QString("%1").arg(R_DB_RealRecords) ;}
};

#endif // R_DBLINERECORDS_H
