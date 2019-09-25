#ifndef SILOGTHRESHOLDWID_H
#define SILOGTHRESHOLDWID_H

#include "silogrealrecordwid.h"

class SiLogThresholdWid : public LogComWid
{
    Q_OBJECT
public:
    explicit SiLogThresholdWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // SILOGTHRESHOLDWID_H
