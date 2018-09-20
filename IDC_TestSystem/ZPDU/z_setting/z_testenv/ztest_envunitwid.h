#ifndef ZTEST_ENVUNITWID_H
#define ZTEST_ENVUNITWID_H

#include <QWidget>
#include "ztest_envitemwid.h"
namespace Ui {
class ZTest_EnvUnitWid;
}

class ZTest_EnvUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZTest_EnvUnitWid(QWidget *parent = 0);
    ~ZTest_EnvUnitWid();
    void initWid(int mode, int type);
    void getCmdList(int addr, QList<sZTestRtuSetCmd> &list);

private:
    Ui::ZTest_EnvUnitWid *ui;
    ZTest_EnvItemWid *mWid[4];
};

#endif // ZTEST_ENVUNITWID_H
