#ifndef SIDBREALRECORDS_H
#define SIDBREALRECORDS_H
#include "sqlcom/dblinerecords.h"

#define SI_DB_RealRecords "si_line_records"

class SiDbRealRecords : public DbLineRecords
{
    SiDbRealRecords();
public:
    static SiDbRealRecords *bulid();
    virtual QString tableName(){return QString("%1").arg(SI_DB_RealRecords) ;}   
};

#endif // SIDBREALRECORDS_H
