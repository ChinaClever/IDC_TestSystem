#ifndef BUS_DPTHREAD_H
#define BUS_DPTHREAD_H

#include <QObject>

class BUS_DpThread : public QObject
{
    Q_OBJECT
public:
    explicit BUS_DpThread(QObject *parent = nullptr);

signals:

public slots:
};

#endif // BUS_DPTHREAD_H