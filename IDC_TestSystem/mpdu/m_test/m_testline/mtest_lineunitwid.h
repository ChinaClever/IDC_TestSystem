#ifndef MTEST_LINEUNITWID_H
#define MTEST_LINEUNITWID_H

#include "mtest_lineitemwid.h"

namespace Ui {
class MTest_LineUnitWid;
}

class MTest_LineUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit MTest_LineUnitWid(QWidget *parent = 0);
    ~MTest_LineUnitWid();

    void initWid(int mode, int type);
    void getCmdList(int addr, QList<sMTestRtuSetCmd> &list);

private:
    Ui::MTest_LineUnitWid *ui;
    MTest_LineItemWid *mWid[3];
};

#endif // MTEST_LINEUNITWID_H
