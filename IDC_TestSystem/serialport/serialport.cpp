/*
 * 对串口的常用操作：打开、读、写、关闭
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "serialport.h"
#include <QSerialPortInfo>

SerialPort::SerialPort(QObject *parent) : QObject(parent)
{
    isOpen = false;
    mSerial = NULL;
}

SerialPort::~SerialPort()
{
    close();
}

/**
 * @brief 打开串口
 * @param name 串口名  大写
 * @param baudRate 波特率
 * @return true
 */
bool SerialPort::open(const QString &name,qint32 baudRate)
{
    bool ret=false;

    if(!isOpen)
    {
        mSerial = new QSerialPort(name);       //串口号，一定要对应好，大写！！！
        ret = mSerial->open(QIODevice::ReadWrite);      //读写打开
        if(ret)
        {
            mSerial->setBaudRate(baudRate);  //波特率
            mSerial->setDataBits(QSerialPort::Data8); //数据位
            mSerial->setParity(QSerialPort::NoParity);    //无奇偶校验
            mSerial->setStopBits(QSerialPort::OneStop);   //无停止位
            mSerial->setFlowControl(QSerialPort::NoFlowControl);  //无控制
            // connect(mSerial,SIGNAL(readyRead()),this,SLOT(serialReadSlot()));    //连接槽
            isOpen = true;
        }
        else
            qDebug() << "open Serial:" << name << "Err";
    }

    return ret;
}


/**
 * @brief 串口关闭
 * @return true
 */
bool SerialPort::close(void)
{
    if(isOpen)
    {
        QWriteLocker locker(&mRwLock); // 正在操作时不允许关闭
        isOpen = false;
        mSerial->close();
        delete mSerial;
        mSerial = NULL;
    }

    return true;
}

/**
 * @brief 获取端口名称
 * @return
 */
QString SerialPort::getSerialName()
{
    QString com;

    if(mSerial)
        com =  mSerial->portName();

    return com;
}


/**
 * @brief 获取串口列表
 * @return
 */
QStringList SerialPort::getList()
{
    QStringList list;
    QList<QSerialPortInfo>  infos = QSerialPortInfo::availablePorts();
    if(!infos.isEmpty())
    {
        foreach (QSerialPortInfo info, infos) {
            list <<  info.portName();
        }
    }

    return list;
}

bool SerialPort::isContains(const QString &name)
{
     return getList().contains(name);
}


/**
 * @brief 写数据
 * @param array
 * @return
 */
int SerialPort::write(const QByteArray &array)
{
    int len=0;

    if(isOpen) {
        len = mSerial->write(array);
        mSerial->flush();
    }

    return len;
}

int SerialPort::write(uchar *sent, int len)
{
    QByteArray array;
    array.append((char *)sent, len);

    return write(array);
}


/**
 * @brief 读串口
 * @param array
 * @return 长度
 */
int SerialPort::read(QByteArray &array)
{
    int len = 0;
    if(!isOpen) return len;

    QWriteLocker locker(&mRwLock);
    for(int i=0; i<5; ++i)
    {
        /* 处理所有还没有被处理的各类事件，主要是不用用户感觉到ka */
        // QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
        // msleep(35);
        serialReadSlot();

        if(mSerialData.size() > len)
            len = mSerialData.size();
        else
            break;
    }

    if(len > 0) array = mSerialData;
    mSerialData.clear();

    return len;
}

int SerialPort::read(uchar *recv)
{
    QByteArray array;
    int ret = read(array);

    for(int i=0; i<ret; ++i)
        recv[i] = array.at(i);

    return ret;
}


/**
 * @brief 串口接收糟函数
 */
void SerialPort::serialReadSlot(void)
{
    if(isOpen)
    {
        QByteArray dataTemp;
        while (mSerial->waitForReadyRead(60)); // 等待窗口接收完全
        while (!mSerial->atEnd())
            dataTemp += mSerial->readAll();     //因为串口是不稳定的，也许读到的是部分数据而已，但也可能是全部数据

        mSerialData += dataTemp;
        //emit readyReadSig();
    }
}

/**
 * @brief 半双工传输
 * @param witeArray 要发送的数据
 * @param readArray 接收到的数据
 * @return 收到的数据长度
 */
int SerialPort::transmit(const QByteArray &witeArray, QByteArray &readArray)
{
    int ret = write(witeArray);
    if(ret > 0)
        ret = read(readArray);
    return ret;
}

/**
  * 功　能：传输数据
  * 入口参数：sent -> 发送缓冲区, len ->  发送长度
  * 出口参数：recv -> 接收缓冲区
  * 返回值：读取的实际长度  <=0 出错
  */
int SerialPort::transmit(uchar *sent, int len, uchar *recv)
{
    int ret = write(sent, len);
    if(ret > 0) {
        ret = read(recv);
        if(ret <=0 )
            qDebug() << "Serial Trans Err!!!";
    }
    return ret;
}


/**
 * @brief 回环测试
 */
void SerialPort::test()
{
    QByteArray sentArray,recvArray;

    for(int i=0; i<255;++i)
        sentArray.append(i);

    int ret = transmit(sentArray, recvArray);
    if(ret != sentArray.size())
        qDebug() << "Serial test Err:" <<ret;
    else
        qDebug() << "Serial test OK";
}
