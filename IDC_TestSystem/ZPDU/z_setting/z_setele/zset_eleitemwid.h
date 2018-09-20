#ifndef ZSET_ELEITEMWID_H
#define ZSET_ELEITEMWID_H

#include <QWidget>
#include "common.h"
namespace Ui {
class ZSet_EleItemWid;
}

class ZSet_EleItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_EleItemWid(QWidget *parent = 0);
    ~ZSet_EleItemWid();

    void init(int id);
    void setSelect(bool checked);
    void setClean(bool checked);

    bool select();
    int status();


private slots:
    void on_cleanRadio_clicked();

private:
    Ui::ZSet_EleItemWid *ui;
};

#endif // ZSET_ELEITEMWID_H
