#ifndef R_DBLOOPRECORDS_H
#define R_DBLOOPRECORDS_H
#include "sqlcom/dblooprecords.h"

#define R_DB_LoopRecords "r_loop_records"

class R_DbLoopRecords: public DbLoopRecords
{
    R_DbLoopRecords();
public:
    static R_DbLoopRecords *bulid();
    virtual QString tableName(){return QString("%1").arg(R_DB_LoopRecords) ;}
};

#endif // R_DBLOOPRECORDS_H
