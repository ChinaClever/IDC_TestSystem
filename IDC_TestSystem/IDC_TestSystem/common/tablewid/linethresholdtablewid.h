#ifndef LINETHRESHOLDTABLEWID_H
#define LINETHRESHOLDTABLEWID_H

#include "linetablewid.h"

class LineThresholdTableWid : public LineTableWid
{
    Q_OBJECT
public:
    explicit LineThresholdTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    void setAlarm(sObjData &unit,int row);
    void setObjUnit(sObjData &unit, QStringList &list);
};

#endif // LINETHRESHOLDTABLEWID_H
