#ifndef MV1SET_ENVUNITWID_H
#define MV1SET_ENVUNITWID_H

#include "mv1set_envitemwid.h"

namespace Ui {
class MV1Set_EnvUnitWid;
}

class MV1Set_EnvUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit MV1Set_EnvUnitWid(QWidget *parent = 0);
    ~MV1Set_EnvUnitWid();

    void initWid(int mode, int type);
    void getCmdList(int addr, QList<sRtuSetCmd> &list);
    void getCmdList(int index ,int addr, QList<sSnmpSetCmd> &list);

private:
    Ui::MV1Set_EnvUnitWid *ui;
    MV1Set_EnvItemWid *mWid[2];
    int getIndex(int index ,int sensorThresholdNumber, int sensorIndex);
};

#endif // MV1SET_ENVUNITWID_H
