#ifndef MTEST_ELEITEMWID_H
#define MTEST_ELEITEMWID_H

#include "../m_testline/mtest_linewid.h"

namespace Ui {
class MTest_EleItemWid;
}

class MTest_EleItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MTest_EleItemWid(QWidget *parent = 0);
    ~MTest_EleItemWid();

    void init(int id);
    void setSelect(bool checked);
    void setClean(bool checked);

    bool select();
    int status();
private slots:
    void on_cleanRadio_clicked();

private:
    Ui::MTest_EleItemWid *ui;
};

#endif // MTEST_ELEITEMWID_H
