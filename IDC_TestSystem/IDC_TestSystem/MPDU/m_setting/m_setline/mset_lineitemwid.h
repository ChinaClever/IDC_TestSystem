#ifndef MSET_LINEITEMWID_H
#define MSET_LINEITEMWID_H

#include "../m_setthreshold/mset_thresholdoutputwid.h"

namespace Ui {
class MSet_LineItemWid;
}

class MSet_LineItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MSet_LineItemWid(QWidget *parent = 0);
    ~MSet_LineItemWid();

    void initwid(int mode, int type);

    int mReg;
    MSet_ThresholdItemWid *mWid[3];

protected:
    QString getTypeName(int type);
    int getReg(int mode, int type);

private:
    Ui::MSet_LineItemWid *ui;
};

#endif // MSET_LINEITEMWID_H
