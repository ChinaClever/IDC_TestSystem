#ifndef Z_DBLINETHRESHOLDS_H
#define Z_DBLINETHRESHOLDS_H
#include "sqlcom/dblinethresholds.h"

#define Z_DB_Thresholds "z_line_thresholds"

class Z_DbLineThresholds : public DbLineThresholds
{
    Z_DbLineThresholds();
public:
    static Z_DbLineThresholds *bulid();
    virtual QString tableName(){return QString("%1").arg(Z_DB_Thresholds) ;}
};

#endif // Z_DBLINETHRESHOLDS_H
