#ifndef RSET_LINEWID_H
#define RSET_LINEWID_H

#include <QWidget>
#include "rset_lineunitwid.h"
namespace Ui {
class RSet_LineWid;
}

class RSet_LineWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_LineWid(QWidget *parent = 0);
    ~RSet_LineWid();

protected:
    void initWid();

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::RSet_LineWid *ui;
    RSet_RtuThread *mRtu;
    RSet_SnmpThread *mSnmp;
    RSet_LineUnitWid *mWid[2];
    void sendSnmp(int addr);
    void sendRtu(int addr);
};

#endif // RSET_LINEWID_H
