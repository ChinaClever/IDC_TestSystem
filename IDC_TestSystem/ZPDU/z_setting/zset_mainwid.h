#ifndef ZSET_MAINWID_H
#define ZSET_MAINWID_H

#include <QWidget>

namespace Ui {
class ZSet_MainWid;
}

class ZSet_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_MainWid(QWidget *parent = 0);
    ~ZSet_MainWid();
protected:
    QString getName(int mode);
protected slots:
    void initFunSLot();

private:
    Ui::ZSet_MainWid *ui;
};

#endif // ZSET_MAINWID_H
