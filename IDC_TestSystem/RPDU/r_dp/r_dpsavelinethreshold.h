#ifndef R_DPSAVELINETHRESHOLD_H
#define R_DPSAVELINETHRESHOLD_H
#include "r_dpsavelinerecord.h"
#include "r_sql/r_dblinethresholds.h"
#include "dpcom/dpsavelinethreshold.h"

class R_DpSaveLineThreshold : public DpSaveLineThreshold
{
    Q_OBJECT
public:
    explicit R_DpSaveLineThreshold(QObject *parent = nullptr);

protected:
    void insertItem(DbLineThresholdItem &item){R_DbLineThresholds::bulid()->insertItem(item);}
};
#endif // R_DPSAVELINETHRESHOLD_H
