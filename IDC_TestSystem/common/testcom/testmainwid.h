#ifndef TESTMAINWID_H
#define TESTMAINWID_H

#include "testdatatablewid.h"
#include "testcorethread.h"
#include "testwebsocket.h"

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
    void overSlot();

protected:
    void startTest();
    void pauseTest();
    void continueTest();
    void overTest();

private:
    TestDataSave *mDataSave;
    TestWebSocket *mWebSocket;
    TestResultWid *mResultWid;
    TestItemTableWid *mItemTableWid;
    TestDataTableWid *mDataTableWid;
    TestSerialNumDlg *mSerialNumDlg;

protected:
    Ui::TestMainWid *ui;

    sDevPackets *mPackets;
    TestConfig *mConfig;
    TestTransThread *mTrans;
    TestCoreThread *mCoreThread;
};

#endif // TESTMAINWID_H
