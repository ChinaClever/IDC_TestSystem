#ifndef RSET_ENVUNITWID_H
#define RSET_ENVUNITWID_H

#include <QWidget>
#include "rset_envitemwid.h"
namespace Ui {
class RSet_EnvUnitWid;
}

class RSet_EnvUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_EnvUnitWid(QWidget *parent = 0);
    ~RSet_EnvUnitWid();
    void initWid(int mode, int type);
    void getCmdList(int addr, QList<sRtuSetCmd> &list);
    void getCmdList(int index ,int addr, QList<sSnmpSetCmd> &list);

private:
    Ui::RSet_EnvUnitWid *ui;
    RSet_EnvItemWid *mWid[4];
    int getIndex(int index ,int sensorThresholdNumber, int sensorIndex);
};

#endif // RSET_ENVUNITWID_H
