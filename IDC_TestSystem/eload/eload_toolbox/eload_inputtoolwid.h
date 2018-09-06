#ifndef ELOAD_INPUTTOOLWID_H
#define ELOAD_INPUTTOOLWID_H

#include "eload_hometoolwid.h"

namespace Ui {
class ELoad_InputToolWid;
}

class ELoad_InputToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit ELoad_InputToolWid(QWidget *parent = 0);
    ~ELoad_InputToolWid();

signals:
    void toolSig(int);

private slots:
    void on_realBtn_clicked();
    void on_thresholdBtn_clicked();
    void on_transBtn_clicked();
    void on_envBtn_clicked();
    void on_setBtn_clicked();

private:
    Ui::ELoad_InputToolWid *ui;
};

#endif // ELOAD_INPUTTOOLWID_H
