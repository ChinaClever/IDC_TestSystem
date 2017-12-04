#ifndef SILOGMODBUSCMDWID_H
#define SILOGMODBUSCMDWID_H

#include "logcom/logcomwid.h"

class SiLogModbusCmdWid : public LogComWid
{
    Q_OBJECT
public:
    explicit SiLogModbusCmdWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // SILOGMODBUSCMDWID_H
