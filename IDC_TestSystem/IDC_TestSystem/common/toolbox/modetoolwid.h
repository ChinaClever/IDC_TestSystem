#ifndef MODETOOLWID_H
#define MODETOOLWID_H

#include "settingtoolwid.h"

namespace Ui {
class ModeToolWid;
}

class ModeToolWid : public QWidget
{
    Q_OBJECT

public:
    explicit ModeToolWid(QWidget *parent = 0);
    ~ModeToolWid();

    void sipdu();
    void init(ConfigBase *config) {mConfig= config;}

signals:
    void simulateSig(int);

protected:
    bool initSerialPort();
    void updateSerialWid();
    void startTest();
    bool stopTest();
    bool checkInput();

    void initDevNum();
    void updateDevNum(int num);

protected slots:
    void initFunSLot();
    void on_serialBtn_clicked();
    void on_testBtn_clicked();
    void on_settingBtn_clicked();
    void on_devNumBtn_clicked();
    void on_comboBox_currentIndexChanged(int index);

protected:
    Ui::ModeToolWid *ui;
    SerialPortDlg *mSerialPortDlg;
    ConfigBase *mConfig;
};

#endif // MODETOOLWID_H
