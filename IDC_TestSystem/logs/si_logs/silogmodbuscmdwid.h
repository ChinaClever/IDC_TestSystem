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
    QString getTableName();

protected slots:
    virtual void clearTableSlot();

};

#endif // SILOGMODBUSCMDWID_H
