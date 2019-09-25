#ifndef OUTPUTTHRESHOLDTABLEWID_H
#define OUTPUTTHRESHOLDTABLEWID_H

#include "outputtablewid.h"

class OutputThresholdTableWid : public OutputTableWid
{
    Q_OBJECT
public:
    explicit OutputThresholdTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    void setAlarm(sObjData &unit,int row);
    void setObjUnit(sObjData &unit, QStringList &list);
};

#endif // OUTPUTTHRESHOLDTABLEWID_H
