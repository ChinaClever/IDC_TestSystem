#ifndef MTEST_ENVUNITWID_H
#define MTEST_ENVUNITWID_H

#include "mtest_envitemwid.h"

namespace Ui {
class MTest_EnvUnitWid;
}

class MTest_EnvUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit MTest_EnvUnitWid(QWidget *parent = 0);
    ~MTest_EnvUnitWid();

    void initWid(int mode, int type);
    void getCmdList(int addr, QList<sMTestRtuSetCmd> &list);

private:
    Ui::MTest_EnvUnitWid *ui;
    MTest_EnvItemWid *mWid[3];
};

#endif // MTEST_ENVUNITWID_H
