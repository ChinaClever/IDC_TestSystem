#ifndef SILOGALARMWID_H
#define SILOGALARMWID_H

#include "silogthresholdwid.h"

class SiLogAlarmWid : public LogComWid
{
    Q_OBJECT
public:
    explicit SiLogAlarmWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // SILOGALARMWID_H
