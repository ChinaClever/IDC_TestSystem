#ifndef IPLOGENVWID_H
#define IPLOGENVWID_H

#include "iplogalarmwid.h"

class IpLogEnvWid : public LogComWid
{
    Q_OBJECT
public:
    explicit IpLogEnvWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // IPLOGENVWID_H
