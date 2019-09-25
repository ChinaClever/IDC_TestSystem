#ifndef Z_SERVICETHREAD_H
#define Z_SERVICETHREAD_H

#include "json/z_buildjson.h"

class Z_ServiceThread : public WebServiceThread
{
    Q_OBJECT
public:
    explicit Z_ServiceThread(QObject *parent = nullptr);

signals:

public slots:
};

#endif // Z_SERVICETHREAD_H
