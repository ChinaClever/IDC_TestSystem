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

private slots:
    void on_resultBtn_clicked();
    void on_testItemBtn_clicked();
    void on_testDataBtn_clicked();
    void on_startBtn_clicked();
    void on_pauseBtn_clicked();
    void on_overBtn_clicked();
    void on_continueBtn_clicked();

private:
    Ui::TestToolWid *ui;
};

#endif // TESTTOOLWID_H
