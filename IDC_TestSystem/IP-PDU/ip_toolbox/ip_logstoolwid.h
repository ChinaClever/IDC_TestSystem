#ifndef IP_LOGSTOOLWID_H
#define IP_LOGSTOOLWID_H

#include "ip_simulationtoolwid.h"

namespace Ui {
class IP_LogsToolWid;
}

class IP_LogsToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit IP_LogsToolWid(QWidget *parent = 0);
    ~IP_LogsToolWid();

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
    void on_thresholdBtn_clicked();
    void on_alarmBtn_clicked();
    void on_timeBtn_clicked();

private:
    Ui::IP_LogsToolWid *ui;
};

#endif // IP_LOGSTOOLWID_H
