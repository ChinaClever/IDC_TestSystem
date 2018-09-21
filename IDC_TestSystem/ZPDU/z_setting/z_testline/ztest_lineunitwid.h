#ifndef ZTEST_LINEUNITWID_H
#define ZTEST_LINEUNITWID_H

#include <QWidget>
#include "ztest_lineitemwid.h"
namespace Ui {
class ZTest_LineUnitWid;
}

class ZTest_LineUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZTest_LineUnitWid(QWidget *parent = 0);
    ~ZTest_LineUnitWid();

    void initWid(int mode, int type);
    void getCmdList(int addr, QList<sRtuSetCmd> &list);
private:
    Ui::ZTest_LineUnitWid *ui;
    ZTest_LineItemWid *mWid[4];
};

#endif // ZTEST_LINEUNITWID_H
