#ifndef BUS_DPSLAVETRANS_H
#define BUS_DPSLAVETRANS_H
#include "bus_dpslaveenv.h"

class BUS_DpSlaveTrans : public BUS_DpSlaveRecord
{
public:
    BUS_DpSlaveTrans(QObject *parent = nullptr);

protected:
    void saveItem(QStringList &list, BUS_RtuCount &unit);
    void saveBox(int busId,int boxId);
};

#endif // BUS_DPSLAVETRANS_H
