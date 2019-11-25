#ifndef MV1_LOGLINETHRESHOLDWID_H
#define MV1_LOGLINETHRESHOLDWID_H

#include "mv1_loglinerecordwid.h"

class MV1_LogLineThresholdWid : public LogComWid
{
    Q_OBJECT
public:
    explicit MV1_LogLineThresholdWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // MV1_LOGLINETHRESHOLDWID_H
