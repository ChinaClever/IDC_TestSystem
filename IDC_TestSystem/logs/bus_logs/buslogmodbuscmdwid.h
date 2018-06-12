#ifndef BUSLOGMODBUSCMDWID_H
#define BUSLOGMODBUSCMDWID_H

#include "buslogenvwid.h">

class BusLogModbusCmdWid : public LogComWid
{
    Q_OBJECT
public:
    explicit BusLogModbusCmdWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // BUSLOGMODBUSCMDWID_H
