#ifndef MSET_LINEUNITWID_H
#define MSET_LINEUNITWID_H

#include "mset_lineitemwid.h"

namespace Ui {
class MSet_LineUnitWid;
}

class MSet_LineUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit MSet_LineUnitWid(QWidget *parent = 0);
    ~MSet_LineUnitWid();

    void initWid(int mode, int type);
    void getCmdList(int addr, QList<sRtuSetCmd> &list);
    void getCmdList(int index , int addr, QList<sSnmpSetCmd> &list);

private:
    Ui::MSet_LineUnitWid *ui;
    MSet_LineItemWid *mWid[3];
};

#endif // MSET_LINEUNITWID_H
