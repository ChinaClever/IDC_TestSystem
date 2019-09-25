#ifndef BUS_DPSAVETHRESHOLD_H
#define BUS_DPSAVETHRESHOLD_H
#include "bus_dpsaverecord.h"

class BUS_DpSaveThreshold : public BUS_DpSaveRecord
{
public:
    BUS_DpSaveThreshold(QObject *parent = nullptr);

protected:
    void saveLoop(QStringList &list, sObjData &unit);
};

#endif // BUS_DPSAVETHRESHOLD_H
