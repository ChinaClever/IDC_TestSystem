#ifndef TESTRESULTWID_H
#define TESTRESULTWID_H

#include "testserialnumdlg.h"

namespace Ui {
class TestResultWid;
}



class TestResultWid : public QWidget
{
    Q_OBJECT

public:
    explicit TestResultWid(QWidget *parent = 0);
    ~TestResultWid();

    void init(sTestConfigItem *item) {mItem = item;}
    void initStytleSheet();

public slots:
    void startSlot();
    void progressSlot();
    void resultSlot();

private:
    Ui::TestResultWid *ui;

    QTimer *timer;
    sTestConfigItem *mItem;
};

#endif // TESTRESULTWID_H
