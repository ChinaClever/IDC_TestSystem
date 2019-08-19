#ifndef RSET_ENVWID_H
#define RSET_ENVWID_H

#include <QWidget>
#include "rset_envunitwid.h"
namespace Ui {
class RSet_EnvWid;
}

class RSet_EnvWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_EnvWid(QWidget *parent = 0);
    ~RSet_EnvWid();
protected:
    void initWid();

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::RSet_EnvWid *ui;
    RSet_RtuThread *mRtu;
    RSet_SnmpThread *mSnmp;
    RSet_EnvUnitWid *mWid[2];
    void sendSnmp(int addr);
    void sendRtu(int addr);
};

#endif // RSET_ENVWID_H
