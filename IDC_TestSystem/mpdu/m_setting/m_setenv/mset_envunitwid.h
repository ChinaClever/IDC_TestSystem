﻿#ifndef MSET_ENVUNITWID_H
#define MSET_ENVUNITWID_H

#include "mset_envitemwid.h"

namespace Ui {
class MSet_EnvUnitWid;
}

class MSet_EnvUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit MSet_EnvUnitWid(QWidget *parent = 0);
    ~MSet_EnvUnitWid();

    void initWid(int mode, int type);
    void getCmdList(int addr, QList<sMTestRtuSetCmd> &list);

private:
    Ui::MSet_EnvUnitWid *ui;
    MSet_EnvItemWid *mWid[3];
};

#endif // MSET_ENVUNITWID_H
