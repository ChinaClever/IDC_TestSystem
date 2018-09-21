#ifndef ZSET_LOOPUNITWID_H
#define ZSET_LOOPUNITWID_H

#include <QWidget>
#include "zset_loopitemwid.h"
#define LOOPCURRATE 100
namespace Ui {
class ZSet_LoopUnitWid;
}

class ZSet_LoopUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_LoopUnitWid(QWidget *parent = 0);
    ~ZSet_LoopUnitWid();

    void initWid(int type);
    void getCmdList(int addr, QList<sRtuSetCmd> &list);
    void getCmdList(int addr, QList<sSnmpSetCmd> &list);
private:
    Ui::ZSet_LoopUnitWid *ui;
    ZSet_LoopItemWid *mWid[4];
};

#endif // ZSET_LOOPUNITWID_H
