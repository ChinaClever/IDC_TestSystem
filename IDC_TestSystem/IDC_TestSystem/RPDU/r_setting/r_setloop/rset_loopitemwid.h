#ifndef RSET_LOOPITEMWID_H
#define RSET_LOOPITEMWID_H

#include <QWidget>
#include "../r_setthreshold/rset_thresholdoutputwid.h"
namespace Ui {
class RSet_LoopItemWid;
}

class RSet_LoopItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_LoopItemWid(QWidget *parent = 0);
    ~RSet_LoopItemWid();

    void initwid(int type);

    int mReg;
    RSet_ThresholdItemWid *mWid[6];

protected:
    QString getTypeName(int type);
    int getReg(int type);
private:
    Ui::RSet_LoopItemWid *ui;
};

#endif // RET_LOOPITEMWID_H
