#ifndef TRANSTABLEWID_H
#define TRANSTABLEWID_H

#include "envtablewid.h"

class TransTableWid : public LineTableWid
{
    Q_OBJECT
public:
    explicit TransTableWid(QWidget *parent = nullptr);

protected:
    void initWid();
    void setAlarm(int err, int row);
    void setObjUnit(sRtuCount &unit, QStringList &list);
    int updateDev(sDataPacket *dev, int row);
};

#endif // TRANSTABLEWID_H
