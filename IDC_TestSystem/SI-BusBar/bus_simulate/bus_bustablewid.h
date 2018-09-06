#ifndef BUS_BUSTABLEWID_H
#define BUS_BUSTABLEWID_H

#include "bus_looptablewid.h"

class BUS_BusTableWid : public BUS_LoopTableWid
{
    Q_OBJECT
public:
    explicit BUS_BusTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    void setLineName(sDataPacket &box);
    int updateBox(sDataPacket &box, const QString &bus, int row);
    int updateBus(sBusData *bus, int row);
};

#endif // BUS_BUSTABLEWID_H
