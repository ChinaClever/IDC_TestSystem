#ifndef BUS_DPSLAVEENV_H
#define BUS_DPSLAVEENV_H
#include "bus_dpsavethreshold.h"

class BUS_DpSaveEnv : public BUS_DpSaveRecord
{
public:
    BUS_DpSaveEnv(QObject *parent = nullptr);

protected:
    void saveLoop(QStringList &list, sDataUnit &unit);
    void saveBox(int busId,int boxId);
};

#endif // BUS_DPSLAVEENV_H
