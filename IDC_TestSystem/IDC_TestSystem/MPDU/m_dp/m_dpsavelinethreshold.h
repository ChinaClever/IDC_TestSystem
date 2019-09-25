#ifndef M_DPSAVELINETHRESHOLD_H
#define M_DPSAVELINETHRESHOLD_H
#include "m_dpalarmsave.h"
#include "m_sql/m_dblinethresholds.h"
#include "dpcom/dpsavelinethreshold.h"

class M_DpSaveLineThreshold : public DpSaveLineThreshold
{
    Q_OBJECT
public:
    explicit M_DpSaveLineThreshold(QObject *parent = nullptr);

protected:
    void insertItem(DbLineThresholdItem &item){M_DbLineThresholds::bulid()->insertItem(item);}
};

#endif // M_DPSAVELINETHRESHOLD_H
