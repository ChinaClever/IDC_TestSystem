#ifndef BUS_BOXTABLEWID_H
#define BUS_BOXTABLEWID_H

#include "bus_looptablewid.h"

class BUS_BoxTableWid : public BUS_LoopTableWid
{
    Q_OBJECT
public:
    explicit BUS_BoxTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    int updateBox(sDataPacket &box, const QString &bus, int row);
    void setLineName(sDevData &box, int dc);
};

#endif // BUS_BOXTABLEWID_H
