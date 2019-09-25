#ifndef RSET_LOOPWID_H
#define RSET_LOOPWID_H

#include <QWidget>
#include "rset_loopunitwid.h"
namespace Ui {
class RSet_LoopWid;
}

class RSet_LoopWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_LoopWid(QWidget *parent = 0);
    ~RSet_LoopWid();
protected:
    void initWid();

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_pushButton_clicked();


private:
    Ui::RSet_LoopWid *ui;
    RSet_RtuThread *mRtu;
    RSet_SnmpThread *mSnmp;
    RSet_LoopUnitWid *mWid;
    void sendSnmp(int addr);
    void sendRtu(int addr);
};

#endif // RSET_LOOPWID_H
