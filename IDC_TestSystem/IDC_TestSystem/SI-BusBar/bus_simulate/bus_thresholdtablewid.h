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
    void setAlarm(sObjData &unit, int row);
    void setObjUnit(sObjData &unit, QStringList &list);
};

#endif // BUS_THRESHOLDTABLEWID_H
