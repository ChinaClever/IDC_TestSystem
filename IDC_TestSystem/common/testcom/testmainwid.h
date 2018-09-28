#ifndef TESTMAINWID_H
#define TESTMAINWID_H

#include "testdatatablewid.h"
#include "testdatasave.h"

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
    void startTest();
    void pauseTest();
    void continueTest();
    void overTest();

protected:
    Ui::TestMainWid *ui;

    sDevPackets *mPackets;
    TestConfig *mConfig;
    TestSerialNumDlg *mSerialNumDlg;

    TestDataSave *mDataSave;
    TestResultWid *mResultWid;
    TestItemTableWid *mItemTableWid;
    TestDataTableWid *mDataTableWid;
};

#endif // TESTMAINWID_H
