#ifndef LOGSTOOLWID_H
#define LOGSTOOLWID_H

#include "modetoolwid.h"

namespace Ui {
class LogsToolWid;
}

class LogsToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit LogsToolWid(QWidget *parent = 0);
    ~LogsToolWid();

    void mpdu();
    void sipdu();

signals:
    void logsSig(int);

protected:
    void updateLogTime(int num);
    void initLogTime();

protected slots:
    void on_modbusBtn_clicked();
    void on_transBtn_clicked();
    void on_envBtn_clicked();
    void on_recordBtn_clicked();
    void on_loopBtn_clicked();
    void on_outputBtn_clicked();
    void on_thresholdBtn_clicked();
    void on_alarmBtn_clicked();
    void on_timeBtn_clicked();

protected:
    Ui::LogsToolWid *ui;
    ConfigBase *config;
};

#endif // LOGSTOOLWID_H
