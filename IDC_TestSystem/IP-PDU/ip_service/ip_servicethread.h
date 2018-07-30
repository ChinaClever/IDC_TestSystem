#ifndef IP_SERVICETHREAD_H
#define IP_SERVICETHREAD_H

#include "json/ip_buildjson.h"

class IP_ServiceThread : public QThread
{
    Q_OBJECT
public:
    explicit IP_ServiceThread(QObject *parent = nullptr);
    ~IP_ServiceThread();

protected:
    void run();
    void readDevList();

protected slots:
    void timeoutDone();

private:
    IP_BuildJson *mBuildJson;
    WebSocketClient *mWebSocket;
    QTimer *timer;
    bool isRun;
};

#endif // IP_SERVICETHREAD_H
