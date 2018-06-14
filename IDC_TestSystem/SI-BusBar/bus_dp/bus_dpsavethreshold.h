#ifndef BUS_DPSAVETHRESHOLD_H
#define BUS_DPSAVETHRESHOLD_H
#include "bus_dpslaverecord.h"

class BUS_DpSaveThreshold : public BUS_DpSlaveRecord
{
public:
    BUS_DpSaveThreshold(QObject *parent = nullptr);

protected:
    void saveLoop(QStringList &list, BUS_sObjUnit &unit);
};

#endif // BUS_DPSAVETHRESHOLD_H
