#ifndef M_LOGSTOOLWID_H
#define M_LOGSTOOLWID_H

#include "m_com/m_datapackets.h"

namespace Ui {
class M_LogsToolWid;
}

class M_LogsToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit M_LogsToolWid(QWidget *parent = 0);
    ~M_LogsToolWid();

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

    void on_outputBtn_clicked();

private:
    Ui::M_LogsToolWid *ui;
};

#endif // M_LOGSTOOLWID_H
