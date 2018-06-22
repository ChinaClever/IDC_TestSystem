#ifndef BUS_DPSLAVERECORD_H
#define BUS_DPSLAVERECORD_H
#include "bus_dpalarmslave.h"


class BUS_DpSlaveRecord : public QThread
{
public:
    BUS_DpSlaveRecord(QObject *parent = nullptr);
    void run();

protected:
    virtual void saveLoop(QStringList &list, BUS_sObjUnit &unit);
    virtual void saveBus(int id);
    void saveBox(int busId, int boxId);

protected:
    bool isRun;
};

#endif // BUS_DPSLAVERECORD_H
