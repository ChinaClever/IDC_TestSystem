#ifndef BUSLOGREALRECORDWID_H
#define BUSLOGREALRECORDWID_H

#include "buslogmodbustranswid.h"

class BusLogRealRecordWid : public LogComWid
{
    Q_OBJECT
public:
    explicit BusLogRealRecordWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // BUSLOGREALRECORDWID_H
