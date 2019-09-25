#ifndef ELOAD_LOGSTOOLWID_H
#define ELOAD_LOGSTOOLWID_H

#include <QWidget>

namespace Ui {
class ELoad_LogsToolWid;
}

class ELoad_LogsToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit ELoad_LogsToolWid(QWidget *parent = 0);
    ~ELoad_LogsToolWid();

signals:
    void logsSig(int);

protected:
    void updateLogTime(int num);
    void initLogTime();

private slots:
    void on_modbusBtn_clicked();
    void on_transBtn_clicked();
    void on_envBtn_clicked();
    void on_outputBtn_clicked();
    void on_thresholdBtn_clicked();
    void on_alarmBtn_clicked();
    void on_timeBtn_clicked();

private:
    Ui::ELoad_LogsToolWid *ui;
};

#endif // ELOAD_LOGSTOOLWID_H
