#ifndef MTEST_ENVITEMWID_H
#define MTEST_ENVITEMWID_H

#include "../m_testele/mtest_outputelewid.h"

namespace Ui {
class MTest_EnvItemWid;
}

class MTest_EnvItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MTest_EnvItemWid(QWidget *parent = 0);
    ~MTest_EnvItemWid();

    void initwid(int mode, int type);

    int mReg;
    MTest_ThresholdItemWid *mWid[3];

protected:
    QString getTypeName(int type);
    int getReg(int mode, int type);

private:
    Ui::MTest_EnvItemWid *ui;
};

#endif // MTEST_ENVITEMWID_H
