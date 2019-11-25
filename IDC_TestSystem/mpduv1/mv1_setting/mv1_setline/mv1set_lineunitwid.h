#ifndef MV1SET_LINEUNITWID_H
#define MV1SET_LINEUNITWID_H

#include "mv1set_lineitemwid.h"

namespace Ui {
class MV1Set_LineUnitWid;
}

class MV1Set_LineUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit MV1Set_LineUnitWid(QWidget *parent = 0);
    ~MV1Set_LineUnitWid();

    void initWid(int mode, int type);
    void getCmdList(int addr, QList<sRtuSetCmd> &list);
    void getCmdList(int index , int addr, QList<sSnmpSetCmd> &list);

private:
    Ui::MV1Set_LineUnitWid *ui;
    MV1Set_LineItemWid *mWid[3];
};

#endif // MV1SET_LINEUNITWID_H
