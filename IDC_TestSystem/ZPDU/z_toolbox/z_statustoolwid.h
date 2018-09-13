#ifndef Z_STATUSTOOLWID_H
#define Z_STATUSTOOLWID_H

#include "z_logstoolwid.h"

namespace Ui {
class Z_StatusToolWid;
}

class Z_StatusToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit Z_StatusToolWid(QWidget *parent = 0);
    ~Z_StatusToolWid();

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
    Ui::Z_StatusToolWid *ui;
};

#endif // Z_STATUSTOOLWID_H
