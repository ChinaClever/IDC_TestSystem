#ifndef R_LOGLINETHRESHOLDWID_H
#define R_LOGLINETHRESHOLDWID_H

#include "r_loglinerecordwid.h"

class R_LogLineThresholdWid : public LogComWid
{
    Q_OBJECT
public:
    explicit R_LogLineThresholdWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // R_LOGLINETHRESHOLDWID_H
