#ifndef SI_DPSAVETHRESHOLD_H
#define SI_DPSAVETHRESHOLD_H

#include "si_dpalarmsave.h"
#include "dpcom/dpsavelinethreshold.h"
#include "si_sql/sidbthresholds.h"

class SI_DpSaveThreshold : public DpSaveLineThreshold
{
    Q_OBJECT
public:
    explicit SI_DpSaveThreshold(QObject *parent = nullptr);

protected:
    void insertItem(DbLineThresholdItem &item){SiDbThresholds::bulid()->insertItem(item);}
};

#endif // SI_DPSAVETHRESHOLD_H
