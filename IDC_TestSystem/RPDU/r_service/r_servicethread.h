#ifndef R_SERVICETHREAD_H
#define R_SERVICETHREAD_H

#include "json/r_buildjson.h"

class R_ServiceThread : public WebServiceThread
{
    Q_OBJECT
public:
    explicit R_ServiceThread(QObject *parent = nullptr);

signals:

public slots:
};

#endif // R_SERVICETHREAD_H
