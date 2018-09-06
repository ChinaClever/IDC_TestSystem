#ifndef BUS_ENVTABLEWID_H
#define BUS_ENVTABLEWID_H

#include "bus_thresholdtablewid.h"

class BUS_EnvTableWid : public BUS_LoopTableWid
{
    Q_OBJECT
public:
    explicit BUS_EnvTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    void setAlarm(sDataUnit &unit, int row);
    void setObjUnit(sDataUnit &unit, QStringList &list);
    int updateBox(sDataPacket &box, const QString &bus, int row);
};

#endif // BUS_ENVTABLEWID_H
