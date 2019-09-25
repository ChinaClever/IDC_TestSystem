#ifndef Z_DBLINERECORDS_H
#define Z_DBLINERECORDS_H
#include "sqlcom/dblinerecords.h"

#define Z_DB_RealRecords "z_line_records"

class Z_DbLineRecords : public DbLineRecords
{
    Z_DbLineRecords();
public:
    static Z_DbLineRecords *bulid();
    virtual QString tableName(){return QString("%1").arg(Z_DB_RealRecords) ;}
};

#endif // Z_DBLINERECORDS_H
