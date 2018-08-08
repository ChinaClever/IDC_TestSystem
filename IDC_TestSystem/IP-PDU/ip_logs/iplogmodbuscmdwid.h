#ifndef IPLOGMODBUSCMDWID_H
#define IPLOGMODBUSCMDWID_H

#include "iplogenvwid.h"

class IpLogModbusCmdWid : public LogComWid
{
    Q_OBJECT
public:
    explicit IpLogModbusCmdWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // IPLOGMODBUSCMDWID_H
