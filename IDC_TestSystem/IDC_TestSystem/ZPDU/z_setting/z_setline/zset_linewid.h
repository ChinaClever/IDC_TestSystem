#ifndef ZSET_LINEWID_H
#define ZSET_LINEWID_H

#include <QWidget>
#include "zset_lineunitwid.h"
namespace Ui {
class ZSet_LineWid;
}

class ZSet_LineWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_LineWid(QWidget *parent = 0);
    ~ZSet_LineWid();

protected:
    void initWid();

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ZSet_LineWid *ui;
    ZSet_RtuThread *mRtu;
    ZSet_SnmpThread *mSnmp;
    ZSet_LineUnitWid *mWid[2];
    void sendSnmp(int addr);
    void sendRtu(int addr);
};

#endif // ZSET_LINEWID_H
