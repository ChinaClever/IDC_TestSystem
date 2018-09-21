#ifndef ZSET_LINEUNITWID_H
#define ZSET_LINEUNITWID_H

#include <QWidget>
#include "zset_lineitemwid.h"
namespace Ui {
class ZSet_LineUnitWid;
}

class ZSet_LineUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_LineUnitWid(QWidget *parent = 0);
    ~ZSet_LineUnitWid();

    void initWid(int mode, int type);
    void getCmdList(int addr, QList<sRtuSetCmd> &list);
    void getCmdList(int index , int addr, QList<sSnmpSetCmd> &list);
private:
    Ui::ZSet_LineUnitWid *ui;
    ZSet_LineItemWid *mWid[4];
};

#endif // ZSET_LINEUNITWID_H
