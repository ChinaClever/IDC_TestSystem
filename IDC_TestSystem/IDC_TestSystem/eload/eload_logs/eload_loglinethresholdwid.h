#ifndef ELOAD_LOGLINETHRESHOLDWID_H
#define ELOAD_LOGLINETHRESHOLDWID_H
#include "ELoad_loglinerecordwid.h"

class ELoad_LogLineThresholdWid : public LogComWid
{
    Q_OBJECT
public:
    explicit ELoad_LogLineThresholdWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // ELOAD_LOGLINETHRESHOLDWID_H
