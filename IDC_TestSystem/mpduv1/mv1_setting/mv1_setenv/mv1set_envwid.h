#ifndef MV1MSET_ENVWID_H
#define MV1SET_ENVWID_H

#include "mv1set_envunitwid.h"

namespace Ui {
class MV1Set_EnvWid;
}

class MV1Set_EnvWid : public QWidget
{
    Q_OBJECT

public:
    explicit MV1Set_EnvWid(QWidget *parent = 0);
    ~MV1Set_EnvWid();

protected:
    void initWid();

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MV1Set_EnvWid *ui;
    MV1Set_RtuThread *mRtu;
    MV1Set_SnmpThread* mSnmp;
    MV1Set_EnvUnitWid *mWid[2];
    void sendSnmp(int addr);
    void sendRtu(int addr);
};

#endif // MV1SET_ENVWID_H
