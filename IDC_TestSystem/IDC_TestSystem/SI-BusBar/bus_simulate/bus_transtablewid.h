#ifndef BUS_TRANSTABLEWID_H
#define BUS_TRANSTABLEWID_H

#include "bus_looptablewid.h"

class BUS_TransTableWid : public BUS_LoopTableWid
{
    Q_OBJECT
public:
    explicit BUS_TransTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    void setAlarm(int err, int row);
    void setObjUnit(sRtuCount &unit, QStringList &list);
    int updateBox(sDataPacket &box, const QString &bus, int row);
    int updateBus(sBusData *bus, int row);
};

#endif // BUS_TRANSTABLEWID_H
