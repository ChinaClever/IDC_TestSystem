#ifndef BUS_DPSLAVERECORD_H
#define BUS_DPSLAVERECORD_H
#include "bus_dpalarmsave.h"


class BUS_DpSaveRecord : public QThread
{
public:
    BUS_DpSaveRecord(QObject *parent = nullptr);
    void run();

protected:
    virtual void saveLoop(QStringList &list, BUS_sObjUnit &unit);
    virtual void saveBus(int id);
    void saveBox(int busId, int boxId);

protected:
    bool isRun;
};

#endif // BUS_DPSLAVERECORD_H
