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

signals:
    void logsSig(int);

private slots:
    void on_modbusBtn_clicked();

private:
    Ui::SiLogsToolWid *ui;
};

#endif // SILOGSTOOLWID_H
