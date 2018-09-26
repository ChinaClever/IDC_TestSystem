#ifndef MSET_ENVWID_H
#define MSET_ENVWID_H

#include "mset_envunitwid.h"

namespace Ui {
class MSet_EnvWid;
}

class MSet_EnvWid : public QWidget
{
    Q_OBJECT

public:
    explicit MSet_EnvWid(QWidget *parent = 0);
    ~MSet_EnvWid();

protected:
    void initWid();

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MSet_EnvWid *ui;
    MSet_RtuThread *mRtu;
    MSet_SnmpThread* mSnmp;
    MSet_EnvUnitWid *mWid[2];
    void sendSnmp(int addr);
    void sendRtu(int addr);
};

#endif // MSET_ENVWID_H
