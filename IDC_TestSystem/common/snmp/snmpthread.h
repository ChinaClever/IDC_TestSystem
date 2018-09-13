#ifndef SNMP_H
#define SNMP_H

#include <QThread>
#include <QScopedPointer>
#include <QMap>
#include <QtSnmpClient.h>
#include <QtCore>
#include "datapacket.h"

#define MIB_OID_CLEVER  ".1.3.6.1.4.1.30966"

class SnmpThread : public QThread
{
    Q_OBJECT
public:
    explicit SnmpThread(QObject *parent = nullptr);
    ~SnmpThread();

    qint32 requestValue( const QString& oid) {return m_snmp_client->requestValue(oid);}
    qint32 requestValues( const QStringList& oid_list ) {return m_snmp_client->requestValues(oid_list); }
    qint32 requestSubValues( const QString& oid ) {return m_snmp_client->requestSubValues(oid);}
    qint32 setValue(const QString& oid, const int type, const QByteArray& value );

    void startRun(const QString &addr, int msec=0);
    void stopRun();
signals:

protected:
    virtual QStringList getRequestValues(int id) = 0;
    virtual int getRequestSubValues(int id, QStringList &oid) = 0;
    virtual void workDown(const QString &ip, const QByteArray &oid, const QByteArray &data)=0;

private:
    void run();
    bool requestValues(int id);
    bool requestSubValues(int id);
    void sentOkCmd();
    void clearCount();
    void setOffLine();
    void setAllOffLine();
    void saveErrCmd();

private slots:
    void onResponseReceived( const qint32 request_id,const QtSnmpDataList& );
    void onRequestFailed( const qint32 request_id );
    void makeRequest();

private:
    QMutex *mMutex;
    QString m_address;
    QtSnmpClient *m_snmp_client;
    QTimer *m_timer;
    QStringList mOidSubList;
    QtSnmpDataList mValues;

    bool isRun;
    int mOidSubIndex, mId;
    sDataPacket *mDataPacket;

protected:
    sDevPackets *mPackets;
};

#endif // SNMP_H