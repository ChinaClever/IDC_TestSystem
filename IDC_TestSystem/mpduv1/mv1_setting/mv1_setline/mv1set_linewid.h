#ifndef MV1SET_LINEWID_H
#define MV1SET_LINEWID_H

#include "mv1set_lineunitwid.h"

namespace Ui {
class MV1Set_LineWid;
}

class MV1Set_LineWid : public QWidget
{
    Q_OBJECT

public:
    explicit MV1Set_LineWid(QWidget *parent = 0);
    ~MV1Set_LineWid();

protected:
    void initWid();

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MV1Set_LineWid *ui;
    MV1Set_RtuThread *mRtu;
    MV1Set_SnmpThread *mSnmp;
    MV1Set_LineUnitWid *mWid[3];
    void sendSnmp(int addr);
    void sendRtu(int addr);
};

#endif // MV1SET_LINEWID_H
