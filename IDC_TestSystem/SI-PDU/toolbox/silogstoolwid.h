#ifndef SILOGSTOOLWID_H
#define SILOGSTOOLWID_H

#include <QWidget>

namespace Ui {
class SiLogsToolWid;
}

class SiLogsToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit SiLogsToolWid(QWidget *parent = 0);
    ~SiLogsToolWid();

protected:
    void initLogTime();
    void updateLogTime(int num);

signals:
    void logsSig(int);

private slots:
    void on_modbusBtn_clicked();

    void on_timeBtn_clicked();

    void on_transBtn_clicked();

    void on_envBtn_clicked();

    void on_recordBtn_clicked();

    void on_thresholdBtn_clicked();

private:
    Ui::SiLogsToolWid *ui;
};

#endif // SILOGSTOOLWID_H
