#ifndef BUS_DPSLAVEENV_H
#define BUS_DPSLAVEENV_H
#include "bus_dpsavethreshold.h"

class BUS_DpSlaveEnv : public BUS_DpSlaveRecord
{
public:
    BUS_DpSlaveEnv(QObject *parent = nullptr);

protected:
    void saveLoop(QStringList &list, BUS_sDataUnit &unit);
    void saveBox(int busId,int boxId);
};

#endif // BUS_DPSLAVEENV_H
