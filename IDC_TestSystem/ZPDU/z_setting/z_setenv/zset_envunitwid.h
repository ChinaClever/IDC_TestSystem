#ifndef ZSET_ENVUNITWID_H
#define ZSET_ENVUNITWID_H

#include <QWidget>
#include "zset_envitemwid.h"
namespace Ui {
class ZSet_EnvUnitWid;
}

class ZSet_EnvUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_EnvUnitWid(QWidget *parent = 0);
    ~ZSet_EnvUnitWid();
    void initWid(int mode, int type);
    void getCmdList(int addr, QList<sRtuSetCmd> &list);

private:
    Ui::ZSet_EnvUnitWid *ui;
    ZSet_EnvItemWid *mWid[4];
};

#endif // ZSET_ENVUNITWID_H
