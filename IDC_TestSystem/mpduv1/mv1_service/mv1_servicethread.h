#ifndef MV1_SERVICETHREAD_H
#define MV1_SERVICETHREAD_H

#include "json/mv1_buildjson.h"

class MV1_ServiceThread : public WebServiceThread
{
    Q_OBJECT
public:
    explicit MV1_ServiceThread(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MV1_SERVICETHREAD_H
