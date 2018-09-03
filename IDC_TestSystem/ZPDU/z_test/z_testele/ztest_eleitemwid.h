#ifndef ZTEST_ELEITEMWID_H
#define ZTEST_ELEITEMWID_H

#include <QWidget>
#include "common.h"
namespace Ui {
class ZTest_EleItemWid;
}

class ZTest_EleItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZTest_EleItemWid(QWidget *parent = 0);
    ~ZTest_EleItemWid();

    void init(int id);
    void setSelect(bool checked);
    void setClean(bool checked);

    bool select();
    int status();


private slots:
    void on_cleanRadio_clicked();

private:
    Ui::ZTest_EleItemWid *ui;
};

#endif // ZTEST_ELEITEMWID_H
