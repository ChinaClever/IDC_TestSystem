#ifndef ZTEST_LOOPUNITWID_H
#define ZTEST_LOOPUNITWID_H

#include <QWidget>
#include "ztest_loopitemwid.h"
namespace Ui {
class ZTest_LoopUnitWid;
}

class ZTest_LoopUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZTest_LoopUnitWid(QWidget *parent = 0);
    ~ZTest_LoopUnitWid();

    void initWid(int type);
    void getCmdList(int addr, QList<sZTestRtuSetCmd> &list);
private:
    Ui::ZTest_LoopUnitWid *ui;
    ZTest_LoopItemWid *mWid[4];
};

#endif // ZTEST_LOOPUNITWID_H
