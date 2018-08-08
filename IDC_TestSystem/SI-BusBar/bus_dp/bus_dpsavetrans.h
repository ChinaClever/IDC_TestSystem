#ifndef BUS_DPSLAVETRANS_H
#define BUS_DPSLAVETRANS_H
#include "bus_dpsaveenv.h"

class BUS_DpSaveTrans : public BUS_DpSaveRecord
{
public:
    BUS_DpSaveTrans(QObject *parent = nullptr);

protected:
    void saveItem(QStringList &list, BUS_RtuCount &unit);
    void saveBox(int busId,int boxId);
};

#endif // BUS_DPSLAVETRANS_H
