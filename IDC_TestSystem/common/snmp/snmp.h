#ifndef SNMP_H
#define SNMP_H

#include <QThread>
#include <QScopedPointer>
#include <QMap>
#include <QtSnmpClient.h>
#include <QtCore>

class Snmp : public QThread
{
    Q_OBJECT
public:
    explicit Snmp(QObject *parent = nullptr);

    void requestValue( const QString& oid) { QMutexLocker locker(mMutex); mOidList << oid;}
    void requestValues( const QStringList& oid_list ){ QMutexLocker locker(mMutex); mOidList <<oid_list;}
    void requestSubValues( const QString& oid ) { QMutexLocker locker(mMutex); mOidSubList << oid;}
    qint32 setValue(const QString& oid, const int type, const QByteArray& value );

signals:

public slots:
    void onResponseReceived( const qint32 request_id,const QtSnmpDataList& );
    void onRequestFailed( const qint32 request_id );
    void makeRequest();

private:
    QMutex *mMutex;
    const QHostAddress m_address;
    QScopedPointer< QtSnmpClient > m_snmp_client;
    QScopedPointer< QTimer > m_timer;
    QStringList mOidList, mOidSubList;
};

#endif // SNMP_H
