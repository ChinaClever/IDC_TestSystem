#ifndef IPLOGREALRECORDWID_H
#define IPLOGREALRECORDWID_H

#include "iplogmodbustranswid.h"

class IpLogRealRecordWid : public LogComWid
{
    Q_OBJECT
public:
    explicit IpLogRealRecordWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // IPLOGREALRECORDWID_H
