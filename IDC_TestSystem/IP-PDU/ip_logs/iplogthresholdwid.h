#ifndef IPLOGTHRESHOLDWID_H
#define IPLOGTHRESHOLDWID_H

#include "iplogrealrecordwid.h"

class IpLogThresholdWid : public LogComWid
{
    Q_OBJECT
public:
    explicit IpLogThresholdWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // IPLOGTHRESHOLDWID_H
