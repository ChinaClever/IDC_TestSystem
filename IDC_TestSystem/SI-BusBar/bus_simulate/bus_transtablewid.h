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
    void setObjUnit(BUS_RtuCount &unit, QStringList &list);
    int updateBox(sBoxData &box, const QString &bus, int row);
};

#endif // BUS_TRANSTABLEWID_H
