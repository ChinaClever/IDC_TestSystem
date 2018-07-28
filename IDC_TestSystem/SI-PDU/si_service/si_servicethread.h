#ifndef SI_SERVICETHREAD_H
#define SI_SERVICETHREAD_H

#include "json/si_buildjson.h"
#include "websocket/websocketclient.h"

class SI_ServiceThread : public QThread
{
    Q_OBJECT
public:
    explicit SI_ServiceThread(QObject *parent = nullptr);
    ~SI_ServiceThread();

protected:
    void run();
    void readDevList();

protected slots:
    void timeoutDone();

private:
    SI_BuildJson *mBuildJson;
    WebSocketClient *mWebSocket;
    QTimer *timer;
    bool isRun;
};

#endif // SI_SERVICETHREAD_H
