#ifndef BUSLOGENVWID_H
#define BUSLOGENVWID_H

#include "buslogalarmwid.h"

class BusLogEnvWid : public LogComWid
{
    Q_OBJECT
public:
    explicit BusLogEnvWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // BUSLOGENVWID_H
