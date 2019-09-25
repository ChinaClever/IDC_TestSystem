#ifndef Z_DPSAVELINETHRESHOLD_H
#define Z_DPSAVELINETHRESHOLD_H
#include "z_dpsavelinerecord.h"
#include "z_sql/z_dblinethresholds.h"
#include "dpcom/dpsavelinethreshold.h"

class Z_DpSaveLineThreshold : public DpSaveLineThreshold
{
    Q_OBJECT
public:
    explicit Z_DpSaveLineThreshold(QObject *parent = nullptr);

protected:
    void insertItem(DbLineThresholdItem &item){Z_DbLineThresholds::bulid()->insertItem(item);}
};
#endif // Z_DPSAVELINETHRESHOLD_H
