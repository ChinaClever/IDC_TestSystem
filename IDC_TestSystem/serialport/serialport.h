#ifndef SERIALPORT_H
#define SERIALPORT_H

#include "common.h"
#include <QSerialPort>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = nullptr);
    ~SerialPort();

    bool open(const QString &name,qint32 baudRate = QSerialPort::Baud9600);
    bool isOpened(){return isOpen;}
    bool close(void);

    QStringList getList();
    QString getSerialName();
    bool isContains(const QString &name);

    int write(const QByteArray &array);
    int write(uchar *sent, int len);

    int read(QByteArray &array);
    int read(uchar *recv);

    int transmit(const QByteArray &witeArray, QByteArray &readArray);
    int transmit(uchar *sent, int len, uchar *recv);

    void test();

signals:

private slots:
    void serialReadSlot(void);

private:
    bool isOpen;
    QSerialPort  *mSerial;
    QReadWriteLock  mRwLock;
    QByteArray mSerialData;
};

#endif // SERIALPORT_H