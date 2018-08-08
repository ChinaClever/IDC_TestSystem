#ifndef M_DBLINETHRESHOLDS_H
#define M_DBLINETHRESHOLDS_H
#include "sqlcom/dblinethresholds.h"

#define M_DB_Thresholds "m_line_thresholds"

class M_DbLineThresholds : public DbLineThresholds
{
    M_DbLineThresholds();
public:
    static M_DbLineThresholds *bulid();
    virtual QString tableName(){return QString("%1").arg(M_DB_Thresholds) ;}
};

#endif // M_DBLINETHRESHOLDS_H
