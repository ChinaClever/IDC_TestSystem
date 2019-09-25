#ifndef ENVTABLEWID_H
#define ENVTABLEWID_H

#include "linethresholdtablewid.h"

class EnvTableWid : public LineTableWid
{
    Q_OBJECT
public:
    explicit EnvTableWid(QWidget *parent = nullptr);


protected:
    void initWid();
    void setAlarm(sEnvData &unit, int id, int row);
    void setObjUnit(sEnvData &unit, int id, QStringList &list);
    int updateDev(sDataPacket *dev, int row);
};

#endif // ENVTABLEWID_H
