#ifndef MSET_LINEWID_H
#define MSET_LINEWID_H

#include "mset_lineunitwid.h"

namespace Ui {
class MSet_LineWid;
}

class MSet_LineWid : public QWidget
{
    Q_OBJECT

public:
    explicit MSet_LineWid(QWidget *parent = 0);
    ~MSet_LineWid();

protected:
    void initWid();

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MSet_LineWid *ui;
    MSet_RtuThread *mRtu;
    MSet_SnmpThread *mSnmp;
    MSet_LineUnitWid *mWid[3];
};

#endif // MSET_LINEWID_H
