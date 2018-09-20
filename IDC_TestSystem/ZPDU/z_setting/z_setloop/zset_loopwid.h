#ifndef ZSET_LOOPWID_H
#define ZSET_LOOPWID_H

#include <QWidget>
#include "zset_loopunitwid.h"
namespace Ui {
class ZSet_LoopWid;
}

class ZSet_LoopWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_LoopWid(QWidget *parent = 0);
    ~ZSet_LoopWid();
protected:
    void initWid();

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_pushButton_clicked();


private:
    Ui::ZSet_LoopWid *ui;
    ZSet_RtuThread *mRtu;
    ZSet_LoopUnitWid *mWid;
};

#endif // ZSET_LOOPWID_H
