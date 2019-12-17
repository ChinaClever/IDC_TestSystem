#ifndef MV1_DBLINETHRESHOLDS_H
#define MV1_DBLINETHRESHOLDS_H
#include "sqlcom/dblinethresholds.h"

#define MV1_DB_Thresholds "mv1_line_thresholds"

class MV1_DbLineThresholds : public DbLineThresholds
{
    MV1_DbLineThresholds();
public:
    static MV1_DbLineThresholds *bulid();
    virtual QString tableName(){return QString("%1").arg(MV1_DB_Thresholds) ;}
};

#endif // MV1_DBLINETHRESHOLDS_H
