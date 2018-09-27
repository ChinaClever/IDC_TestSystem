#ifndef TESTRESULTWID_H
#define TESTRESULTWID_H

#include "testserialnumdlg.h"

namespace Ui {
class TestResultWid;
}

struct sTestProgress
{
    int allNum;
    int errNum;
    int finishNum;
    QString status;
};

class TestResultWid : public QWidget
{
    Q_OBJECT

public:
    explicit TestResultWid(QWidget *parent = 0);
    ~TestResultWid();

public slots:
    void startSlot(QString &name, QString &batch, QString &sn);
    void progressSlot(sTestProgress &arg);
    void resultSlot(bool p);

private:
    Ui::TestResultWid *ui;
};

#endif // TESTRESULTWID_H
