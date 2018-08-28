#ifndef Z_LOGSTOOLWID_H
#define Z_LOGSTOOLWID_H

#include "z_settingtoolwid.h"

namespace Ui {
class Z_LogsToolWid;
}

class Z_LogsToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit Z_LogsToolWid(QWidget *parent = 0);
    ~Z_LogsToolWid();

signals:
    void logsSig(int);

protected:
    void updateLogTime(int num);
    void initLogTime();

private slots:
    void on_modbusBtn_clicked();
    void on_transBtn_clicked();
    void on_envBtn_clicked();
    void on_recordBtn_clicked();
    void on_loopBtn_clicked();
    void on_outputBtn_clicked();
    void on_thresholdBtn_clicked();
    void on_alarmBtn_clicked();
    void on_timeBtn_clicked();

private:
    Ui::Z_LogsToolWid *ui;
};

#endif // Z_LOGSTOOLWID_H
