#ifndef SILOGREALRECORDWID_H
#define SILOGREALRECORDWID_H

#include "silogenvwid.h"

class SiLogRealRecordWid : public LogComWid
{
    Q_OBJECT
public:
    explicit SiLogRealRecordWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // SILOGREALRECORDWID_H
