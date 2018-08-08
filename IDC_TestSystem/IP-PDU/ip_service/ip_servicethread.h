#ifndef IP_SERVICETHREAD_H
#define IP_SERVICETHREAD_H

#include "json/ip_buildjson.h"

class IP_ServiceThread : public WebServiceThread
{
    Q_OBJECT
public:
    explicit IP_ServiceThread(QObject *parent = nullptr);
};

#endif // IP_SERVICETHREAD_H
