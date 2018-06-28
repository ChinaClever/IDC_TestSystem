#ifndef MPDURTUTEST_ENVITEMWID_H
#define MPDURTUTEST_ENVITEMWID_H

#include "../threshold/mpdurtutest_thresholditemwid.h"

namespace Ui {
class MpduRtuTest_EnvItemWid;
}

class MpduRtuTest_EnvItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MpduRtuTest_EnvItemWid(QWidget *parent = 0);
    ~MpduRtuTest_EnvItemWid();
    void initwid(int mode, int type);

    int mReg;
    MpduRtuTest_ThresholdItemWid *mWid[3];

protected:
    QString getTypeName(int type);
    int getReg(int mode, int type);
private:
    Ui::MpduRtuTest_EnvItemWid *ui;
};

#endif // MPDURTUTEST_ENVITEMWID_H
