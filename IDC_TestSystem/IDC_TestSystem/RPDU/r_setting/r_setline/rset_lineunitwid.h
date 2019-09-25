#ifndef RSET_LINEUNITWID_H
#define RSET_LINEUNITWID_H

#include <QWidget>
#include "rset_lineitemwid.h"
namespace Ui {
class RSet_LineUnitWid;
}

class RSet_LineUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_LineUnitWid(QWidget *parent = 0);
    ~RSet_LineUnitWid();

    void initWid(int mode, int type);
    void getCmdList(int addr, QList<sRtuSetCmd> &list);
    void getCmdList(int index , int addr, QList<sSnmpSetCmd> &list);
private:
    Ui::RSet_LineUnitWid *ui;
    RSet_LineItemWid *mWid[4];
};

#endif // RSET_LINEUNITWID_H
