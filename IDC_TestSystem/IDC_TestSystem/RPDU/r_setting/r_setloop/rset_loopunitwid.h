#ifndef RSET_LOOPUNITWID_H
#define RSET_LOOPUNITWID_H

#include <QWidget>
#include "rset_loopitemwid.h"
#define LOOPCURRATE 100
namespace Ui {
class RSet_LoopUnitWid;
}

class RSet_LoopUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_LoopUnitWid(QWidget *parent = 0);
    ~RSet_LoopUnitWid();

    void initWid(int type);
    void getCmdList(int addr, QList<sRtuSetCmd> &list);
    void getCmdList(int addr, QList<sSnmpSetCmd> &list);
private:
    Ui::RSet_LoopUnitWid *ui;
    RSet_LoopItemWid *mWid[4];
};

#endif // RSET_LOOPUNITWID_H
