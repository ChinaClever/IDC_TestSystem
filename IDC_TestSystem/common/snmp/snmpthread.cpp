/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "snmpthread.h"

SnmpThread::SnmpThread(QObject *parent) : QThread(parent)
{
    isRun = false;
    mPackets = nullptr;
    mOidSubIndex = mId = 0;
    mMutex = new QMutex();

    m_snmp_client =  new QtSnmpClient(this);
    m_snmp_client->setCommunity( "public" );
    connect( m_snmp_client,SIGNAL(responseReceived(qint32,QtSnmpDataList)), this, SLOT(onResponseReceived(qint32,QtSnmpDataList)) );
    connect( m_snmp_client, SIGNAL(requestFailed(qint32)), this, SLOT(onRequestFailed(qint32)) );

    m_timer =  new QTimer(this);
    connect( m_timer, SIGNAL(timeout()), SLOT(makeRequest()) );
    connect( m_timer, SIGNAL(timeout()), SLOT(start()));
}

SnmpThread::~SnmpThread()
{
    isRun = false;
    wait();
}

void SnmpThread::startRun(const QString &addr, int msec)
{
    m_address = addr;
    m_snmp_client->setAgentAddress(QHostAddress(addr));

    if(msec == 0) msec = 500 + (rand() % 1000);
    m_timer->start( msec );
    clearCount();
}

void SnmpThread::stopRun()
{
    m_timer->stop();
    isRun = false;
}

qint32 SnmpThread::setValue(const QString& oid, const int type, const QByteArray& value)
{
    return  m_snmp_client->setValue("private", oid, type, value);
}


void SnmpThread::onResponseReceived(const qint32, const QtSnmpDataList& values )
{
    QMutexLocker locker(mMutex);
    mValues << values;
    sentOkCmd();

//    for( const auto& value : values ) {
//        qDebug( "%s | %s : %s\n", qPrintable( m_address ),  qPrintable( value.address() ),  qPrintable( value.data()) );
//    }
}

void SnmpThread::onRequestFailed( const qint32 request_id ) {
    qDebug() << m_address << request_id;
    saveErrCmd();
}


bool SnmpThread::requestValues(int id)
{
    bool ret = false;
    if( ! m_snmp_client->isBusy() ) {
        QStringList oid = getRequestValues(id);
        if(oid.size()) {
            m_snmp_client->requestValues(oid);
            ret = true;
        }
    }

    return ret;
}

bool SnmpThread::requestSubValues(int id)
{
    bool ret = false;

    if(mOidSubIndex < mOidSubList.size()) {
        if( ! m_snmp_client->isBusy() ) {
            m_snmp_client->requestSubValues( mOidSubList.at(mOidSubIndex++));
        }
    } else {
        mOidSubIndex = 0;
        mOidSubList.clear();
        int rtn = getRequestSubValues(id, mOidSubList);
        if(rtn) ret = true;
    }

    return ret;
}

void SnmpThread::setAllOffLine()
{
    if(mPackets) {
        for(int i=0; i<=mPackets->devNum; ++i)
        {
            sDataPacket *packet = &(mPackets->dev[i]);
            packet->offLine = 0;
        }
    }
}

void SnmpThread::setOffLine()
{
    if(mPackets) {
        if(mDataPacket->offLine) mDataPacket->offLine--;
    }
}

void SnmpThread::clearCount()
{
    if(mPackets) {
        for(int i=0; i<=mPackets->devNum; ++i)
        {
            sDataPacket *packet = &(mPackets->dev[i]);
            memset(&(packet->rtuCount), 0, sizeof(sRtuCount));
        }
    }
}


/**
 * @brief 命令传送成功
 * @param devId
 */
void SnmpThread::sentOkCmd()
{
    if(mPackets) {
        mDataPacket->offLine = 10;
        sRtuCount *count = &(mDataPacket->rtuCount);
        count->count++;
        count->okCount ++;
    }
}


/**
 * @brief 保存失败命令
 * @param devId
 */
void SnmpThread::saveErrCmd()
{
    if(mPackets) {
        sRtuCount *count = &(mDataPacket->rtuCount);
        count->count += 1;
        count->errCount += 1;
    }
}


void SnmpThread::makeRequest()
{
    if(mPackets) {
        bool ret = requestSubValues(++mId);
        if(!ret) {
            ret = requestValues(mId);
        }

        if(ret) {
            mDataPacket = &(mPackets->dev[mId]);
        }

        if(mId > mPackets->devNum) {
            mId = 0;
        }
    }
}

void SnmpThread::run()
{
    if(!isRun)
    {
        isRun = true;
        msleep(10);
        QMutexLocker locker(mMutex);
        for( const auto& value : mValues ) {
            workDown(m_address, value.address(), value.data());
        }
        mValues.clear();
        isRun = false;
    }
    if(!m_timer->isActive()) setAllOffLine();
}