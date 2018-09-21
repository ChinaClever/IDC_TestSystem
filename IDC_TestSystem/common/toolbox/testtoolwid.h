#ifndef TESTTOOLWID_H
#define TESTTOOLWID_H

#include "logstoolwid.h"

namespace Ui {
class TestToolWid;
}

class TestToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit TestToolWid(QWidget *parent = 0);
    ~TestToolWid();

signals:
    void simulateSig(int);

private:
    Ui::TestToolWid *ui;
};

#endif // TESTTOOLWID_H
