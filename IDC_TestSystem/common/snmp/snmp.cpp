#include "snmp.h"

Snmp::Snmp(QObject *parent) : QThread(parent)
{
    mMutex = new QMutex();
    m_snmp_client.reset( new QtSnmpClient );
    m_snmp_client->setAgentAddress( m_address );
    m_snmp_client->setCommunity( "public" );

    connect( m_snmp_client.data(),SIGNAL(responseReceived(qint32,QtSnmpDataList)), SLOT(onResponseReceived(qint32,QtSnmpDataList)) );
    connect( m_snmp_client.data(), SIGNAL(requestFailed(qint32)), SLOT(onRequestFailed(qint32)) );

    m_timer.reset( new QTimer );
    connect( m_timer.data(), SIGNAL(timeout()), SLOT(makeRequest()) );
    m_timer->start( 500 + ( rand() % 1000 ) );

    ///////////////////////===================
    ///



}

qint32 Snmp::setValue(const QString& oid, const int type, const QByteArray& value)
{
    return  m_snmp_client->setValue("private", oid, type, value);
}

void Snmp::onResponseReceived(const qint32, const QtSnmpDataList& values )
{
    for( const auto& value : values ) {
        qDebug( "%s | %s : %s\n", qPrintable( m_address.toString() ),  qPrintable( value.address() ),  qPrintable( value.data()) );
    }
}

void Snmp::onRequestFailed( const qint32 request_id ) {
    qDebug() << m_address << request_id;
}

void Snmp::makeRequest() {
    if( ! m_snmp_client->isBusy() ) {
        QMutexLocker locker(mMutex);
        if(mOidList.size()) {
            m_snmp_client->requestValues(mOidList);
            mOidList.clear();
        }

        if(mOidSubList.size()) {
            m_snmp_client->requestSubValues( mOidSubList.first());
            mOidSubList.removeFirst();
        }
    }
}
