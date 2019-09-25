#ifndef ZSET_ENVITEMWID_H
#define ZSET_ENVITEMWID_H

#include <QWidget>
#include "../z_setthreshold/zset_thresholditemwid.h"
namespace Ui {
class ZSet_EnvItemWid;
}

class ZSet_EnvItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_EnvItemWid(QWidget *parent = 0);
    ~ZSet_EnvItemWid();

    void initwid(int mode, int type);

    int mReg;
    ZSet_ThresholdItemWid *mWid[3];

protected:
    QString getTypeName(int type);
    int getReg(int mode, int type);

private:
    Ui::ZSet_EnvItemWid *ui;
};

#endif // ZSET_ENVITEMWID_H
