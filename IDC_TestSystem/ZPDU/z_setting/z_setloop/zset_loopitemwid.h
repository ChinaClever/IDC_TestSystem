#ifndef ZSET_LOOPITEMWID_H
#define ZSET_LOOPITEMWID_H

#include <QWidget>
#include "../z_setthreshold/zset_thresholdoutputwid.h"
namespace Ui {
class ZSet_LoopItemWid;
}

class ZSet_LoopItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_LoopItemWid(QWidget *parent = 0);
    ~ZSet_LoopItemWid();

    void initwid(int type);

    int mReg;
    ZSet_ThresholdItemWid *mWid[6];

protected:
    QString getTypeName(int type);
    int getReg(int type);
private:
    Ui::ZSet_LoopItemWid *ui;
};

#endif // ZSET_LOOPITEMWID_H
