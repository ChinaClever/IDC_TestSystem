#ifndef Z_DBLOOPRECORDS_H
#define Z_DBLOOPRECORDS_H
#include "sqlcom/dblooprecords.h"

#define Z_DB_LoopRecords "z_loop_records"

class Z_DbLoopRecords: public DbLoopRecords
{
    Z_DbLoopRecords();
public:
    static Z_DbLoopRecords *bulid();
    virtual QString tableName(){return QString("%1").arg(Z_DB_LoopRecords) ;}
};

#endif // Z_DBLOOPRECORDS_H
