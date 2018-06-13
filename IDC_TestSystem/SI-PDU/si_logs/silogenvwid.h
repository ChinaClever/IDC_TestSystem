#ifndef SILOGENVWID_H
#define SILOGENVWID_H

#include "silogmodbustranswid.h"

class SiLogEnvWid : public LogComWid
{
    Q_OBJECT
public:
    explicit SiLogEnvWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // SILOGENVWID_H
