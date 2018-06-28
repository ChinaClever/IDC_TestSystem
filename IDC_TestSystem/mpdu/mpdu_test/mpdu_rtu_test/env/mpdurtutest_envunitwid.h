#ifndef MPDURTUTEST_ENVUNITWID_H
#define MPDURTUTEST_ENVUNITWID_H

#include "mpdurtutest_envitemwid.h"

namespace Ui {
class MpduRtuTest_EnvUnitWid;
}

class MpduRtuTest_EnvUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit MpduRtuTest_EnvUnitWid(QWidget *parent = 0);
    ~MpduRtuTest_EnvUnitWid();

    void initWid(int mode, int type);
    void getCmdList(int addr, QList<sMpduRtuTestSetCmd> &list);

private:
    Ui::MpduRtuTest_EnvUnitWid *ui;
    MpduRtuTest_EnvItemWid *mWid[3];
};

#endif // MPDURTUTEST_ENVUNITWID_H
