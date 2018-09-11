#ifndef SNMP_H
#define SNMP_H

#include <QThread>
#include <QScopedPointer>
#include <QMap>
#include <QtSnmpClient.h>
#include <QtCore>

#define MIB_OID_CLEVER  ".1.3.6.1.4.1.30966"

class Snmp : public QThread
{
    Q_OBJECT
public:
    explicit Snmp(QObject *parent = nullptr);
    ~Snmp();

    void requestValue( const QString& oid) { QMutexLocker locker(mMutex); mOidList << oid;}
    void requestValues( const QStringList& oid_list ){ QMutexLocker locker(mMutex); mOidList <<oid_list;}
    void requestSubValues( const QString& oid ) { QMutexLocker locker(mMutex); mOidSubList << oid;}
    qint32 setValue(const QString& oid, const int type, const QByteArray& value );

signals:

public slots:
    void startRun(const QString &addr, int msec=0);
    void stopRun();
    virtual void workDown(const QString &ip, const QByteArray &oid, const QByteArray &data)=0;

private slots:
    void run();
    void onResponseReceived( const qint32 request_id,const QtSnmpDataList& );
    void onRequestFailed( const qint32 request_id );
    void makeRequest();

private:
    QMutex *mMutex;
    QHostAddress m_address;
    QScopedPointer< QtSnmpClient > m_snmp_client;
    QScopedPointer< QTimer > m_timer;
    QStringList mOidList, mOidSubList;
    QtSnmpDataList mValues;
    bool isRun;
};

#endif // SNMP_H
