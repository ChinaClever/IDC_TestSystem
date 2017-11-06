#ifndef SERIALPORTWID_H
#define SERIALPORTWID_H

#include <QWidget>
#include "serialport.h"

namespace Ui {
class SerialPortWid;
}

class SerialPortWid : public QWidget
{
    Q_OBJECT

public:
    explicit SerialPortWid(QWidget *parent = 0);
    ~SerialPortWid();

protected:
    void initSerialPort();
    void initWidget();

protected slots:
    void serialPortChanged(QString com);
    void workBtnSlot();
    void updateBtnSlot();
    void openSerialSlot();

private:
    Ui::SerialPortWid *ui;

    SerialPort *mSerialPort;
};

#endif // SERIALPORTWID_H
