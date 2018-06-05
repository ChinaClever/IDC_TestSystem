#ifndef BUS_TRANSTABLEWID_H
#define BUS_TRANSTABLEWID_H

#include "bus_looptablewid.h"

class BUS_TransTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit BUS_TransTableWid(QWidget *parent = nullptr);

    void updateData();
protected:
    void initWid();
    void setAlarm(int err, int row);
    void setObjUnit(BUS_RtuCount &unit, QStringList &list);
    int updateBox(sBoxData &box, const QString &bus, int row);
    int updateBus(sBusData *bus, int row);
};

#endif // BUS_TRANSTABLEWID_H
