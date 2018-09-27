#ifndef TESTMAINWID_H
#define TESTMAINWID_H

#include "testdatatablewid.h"

namespace Ui {
class TestMainWid;
}

class TestMainWid : public QWidget
{
    Q_OBJECT

public:
    explicit TestMainWid(QWidget *parent = 0);
    ~TestMainWid();

public slots:
    void initFunSLot();
    void updateWidSlot(int id);

protected:
    Ui::TestMainWid *ui;

    TestResultWid *mResultWid;
    TestItemTableWid *mItemTableWid;
    TestDataTableWid *mDataTableWid;
};

#endif // TESTMAINWID_H
