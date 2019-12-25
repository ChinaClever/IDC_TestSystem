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
    int getMode();
private:
    void updateTotalShowWid();
    void updateIndexShowWid(int index);

protected:
    void updateWid();
    bool checkRunTime();
    void updateRunTime();

    void startUp();
    void stopFun();
    void openInput();
    void setMode();
    void show();
    void hide();
signals:
    void updateIndexSig(int index,QString str);
    void sendResistanceCmdSig(int start,int end,int value);

private slots:
    void timeoutDone();
    void sendResFinishSlot();

    void on_startBtn_clicked();
    void on_openBtn_clicked();
    void on_closeBtn_clicked();

    void on_eleBtn_clicked();

    void on_modeBox_currentIndexChanged(int index);

    void on_ResetFirstEloadBtn_clicked();

    void on_ResetSecondEloadBtn_clicked();

    void on_ResetThirdEloadBtn_clicked();

private:
    Ui::ELoad_StatusHomeWid *ui;
    QTimer *timer;

    int mSec;
    bool isRun;
};

#endif // ELOAD_STATUSHOMEWID_H
