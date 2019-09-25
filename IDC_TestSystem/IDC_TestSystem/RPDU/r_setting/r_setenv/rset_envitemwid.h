#ifndef RSET_ENVITEMWID_H
#define RSET_ENVITEMWID_H

#include <QWidget>
#include "../r_setthreshold/rset_thresholditemwid.h"
namespace Ui {
class RSet_EnvItemWid;
}

class RSet_EnvItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_EnvItemWid(QWidget *parent = 0);
    ~RSet_EnvItemWid();

    void initwid(int mode, int type);

    int mReg;
    RSet_ThresholdItemWid *mWid[4];

protected:
    QString getTypeName(int type);
    int getReg(int mode, int type);

private:
    Ui::RSet_EnvItemWid *ui;
};

#endif // RSET_ENVITEMWID_H
