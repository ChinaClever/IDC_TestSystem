#ifndef M_SERVICETHREAD_H
#define M_SERVICETHREAD_H

#include "json/m_buildjson.h"

class M_ServiceThread : public WebServiceThread
{
    Q_OBJECT
public:
    explicit M_ServiceThread(QObject *parent = nullptr);

signals:

public slots:
};

#endif // M_SERVICETHREAD_H
