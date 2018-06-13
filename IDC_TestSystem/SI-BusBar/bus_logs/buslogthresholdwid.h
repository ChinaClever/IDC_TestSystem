#ifndef BUSLOGTHRESHOLDWID_H
#define BUSLOGTHRESHOLDWID_H

#include "buslogrealrecordwid.h"

class BusLogThresholdWid : public LogComWid
{
    Q_OBJECT
public:
    explicit BusLogThresholdWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // BUSLOGTHRESHOLDWID_H
