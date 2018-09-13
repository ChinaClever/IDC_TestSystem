#ifndef STATUSTOOLWID_H
#define STATUSTOOLWID_H

#include "configbase.h"

namespace Ui {
class StatusToolWid;
}

class StatusToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit StatusToolWid(QWidget *parent = 0);
    ~StatusToolWid();

    void mpdu();
    void sipdu();
signals:
    void widSig(int);

private slots:
    void on_devBtn_clicked();
    void on_loopBtn_clicked();
    void on_outputBtn_clicked();
    void on_transBtn_clicked();
    void on_thresholdBtn_clicked();
    void on_loopThresholdBtn_clicked();
    void on_outputThresholdBtn_clicked();
    void on_envBtn_clicked();

private:
    Ui::StatusToolWid *ui;
};

#endif // STATUSTOOLWID_H
