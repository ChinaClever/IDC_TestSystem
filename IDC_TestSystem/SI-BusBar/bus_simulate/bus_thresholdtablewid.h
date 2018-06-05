#ifndef BUS_THRESHOLDTABLEWID_H
#define BUS_THRESHOLDTABLEWID_H

#include "bus_transtablewid.h"

class BUS_ThresholdTableWid : public BUS_LoopTableWid
{
    Q_OBJECT
public:
    explicit BUS_ThresholdTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    void setAlarm(BUS_sObjUnit &unit, int row);
    void setObjUnit(BUS_sObjUnit &unit, QStringList &list);
};

#endif // BUS_THRESHOLDTABLEWID_H
