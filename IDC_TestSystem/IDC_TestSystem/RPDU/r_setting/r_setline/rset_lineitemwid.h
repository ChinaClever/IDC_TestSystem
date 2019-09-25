#ifndef RSET_LINEITEMWID_H
#define RSET_LINEITEMWID_H

#include <QWidget>
#include "../r_setthreshold/rset_thresholdoutputwid.h"
namespace Ui {
class RSet_LineItemWid;
}

class RSet_LineItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_LineItemWid(QWidget *parent = 0);
    ~RSet_LineItemWid();

    void initwid(int mode, int type);

    int mReg;
    int mMode;
    RSet_ThresholdItemWid *mWid[3];

protected:
    QString getTypeName(int type);
    int getReg(int mode, int type);
private:
    Ui::RSet_LineItemWid *ui;
};

#endif // RSET_LINEITEMWID_H
