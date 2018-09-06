#ifndef BUS_LOOPTABLEWID_H
#define BUS_LOOPTABLEWID_H

#include "tablewid/comtablewid.h"
#include "bus_com/buspacketsi.h"

class BUS_LoopTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit BUS_LoopTableWid(QWidget *parent = nullptr);

public slots:
    void updateData();

protected:
    virtual void initWid();
    virtual void setAlarm(sObjData &unit, int row);
    virtual void setObjUnit(sObjData &unit, QStringList &list);
    virtual int updateBox(sDataPacket &box, const QString &bus, int row);
    virtual int updateBus(sBusData *bus, int row);
};

#endif // BUS_LOOPTABLEWID_H
