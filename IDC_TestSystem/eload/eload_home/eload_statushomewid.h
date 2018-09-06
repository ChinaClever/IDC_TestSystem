#ifndef ELOAD_STATUSHOMEWID_H
#define ELOAD_STATUSHOMEWID_H

#include <QWidget>

namespace Ui {
class ELoad_StatusHomeWid;
}

class ELoad_StatusHomeWid : public QWidget
{
    Q_OBJECT

public:
    explicit ELoad_StatusHomeWid(QWidget *parent = 0);
    ~ELoad_StatusHomeWid();

protected:
    void updateWid();
    bool checkRunTime();
    void updateRunTime();

    void startUp();
    void stopFun();
    void openInput();
    void setMode();

private slots:
    void timeoutDone();

    void on_startBtn_clicked();
    void on_openBtn_clicked();
    void on_closeBtn_clicked();

private:
    Ui::ELoad_StatusHomeWid *ui;
    QTimer *timer;

    int mSec;
    bool isRun;
};

#endif // ELOAD_STATUSHOMEWID_H
