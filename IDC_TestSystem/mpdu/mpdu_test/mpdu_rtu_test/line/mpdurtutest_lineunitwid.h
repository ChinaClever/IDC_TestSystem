#ifndef MPDURTUTEST_LINEUNITWID_H
#define MPDURTUTEST_LINEUNITWID_H

#include "mpdurtutest_lineitemwid.h"

namespace Ui {
class MpduRtuTest_LineUnitWid;
}

class MpduRtuTest_LineUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit MpduRtuTest_LineUnitWid(QWidget *parent = 0);
    ~MpduRtuTest_LineUnitWid();

    void initWid(int mode, int type);
    void getCmdList(int addr, QList<sMpduRtuTestSetCmd> &list);

private:
    Ui::MpduRtuTest_LineUnitWid *ui;
    MpduRtuTest_LineItemWid *mWid[3];
};

#endif // MPDURTUTEST_LINEUNITWID_H
