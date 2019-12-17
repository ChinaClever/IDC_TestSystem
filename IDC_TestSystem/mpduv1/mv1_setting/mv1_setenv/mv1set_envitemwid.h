#ifndef MV1SET_ENVITEMWID_H
#define MV1SET_ENVITEMWID_H

#include "../mv1_setele/mv1set_outputelewid.h"

namespace Ui {
class MV1Set_EnvItemWid;
}

class MV1Set_EnvItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MV1Set_EnvItemWid(QWidget *parent = 0);
    ~MV1Set_EnvItemWid();

    void initwid(int mode, int type);

    int mReg;
    MV1Set_ThresholdItemWid *mWid[3];

protected:
    QString getTypeName(int type);
    int getReg(int mode, int type);

private:
    Ui::MV1Set_EnvItemWid *ui;
};

#endif // MV1SET_ENVITEMWID_H
