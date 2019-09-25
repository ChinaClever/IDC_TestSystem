#ifndef MSET_ENVITEMWID_H
#define MSET_ENVITEMWID_H

#include "../m_setele/mset_outputelewid.h"

namespace Ui {
class MSet_EnvItemWid;
}

class MSet_EnvItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MSet_EnvItemWid(QWidget *parent = 0);
    ~MSet_EnvItemWid();

    void initwid(int mode, int type);

    int mReg;
    MSet_ThresholdItemWid *mWid[3];

protected:
    QString getTypeName(int type);
    int getReg(int mode, int type);

private:
    Ui::MSet_EnvItemWid *ui;
};

#endif // MSET_ENVITEMWID_H
