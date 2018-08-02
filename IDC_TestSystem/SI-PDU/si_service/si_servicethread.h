#ifndef SI_SERVICETHREAD_H
#define SI_SERVICETHREAD_H

#include "json/si_buildjson.h"
#include "websocket/websocketclient.h"

class SI_ServiceThread : public WebServiceThread
{
    Q_OBJECT
public:
    explicit SI_ServiceThread(QObject *parent = nullptr);
};

#endif // SI_SERVICETHREAD_H
