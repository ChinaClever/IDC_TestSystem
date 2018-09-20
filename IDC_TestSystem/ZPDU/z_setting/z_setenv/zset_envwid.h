#ifndef ZSET_ENVWID_H
#define ZSET_ENVWID_H

#include <QWidget>
#include "zset_envunitwid.h"
namespace Ui {
class ZSet_EnvWid;
}

class ZSet_EnvWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_EnvWid(QWidget *parent = 0);
    ~ZSet_EnvWid();
protected:
    void initWid();

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ZSet_EnvWid *ui;
    ZSet_RtuThread *mRtu;
    ZSet_EnvUnitWid *mWid[2];
};

#endif // ZSET_ENVWID_H
