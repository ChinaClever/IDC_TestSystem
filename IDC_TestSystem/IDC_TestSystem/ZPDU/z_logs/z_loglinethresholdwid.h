#ifndef Z_LOGLINETHRESHOLDWID_H
#define Z_LOGLINETHRESHOLDWID_H

#include "z_loglinerecordwid.h"

class Z_LogLineThresholdWid : public LogComWid
{
    Q_OBJECT
public:
    explicit Z_LogLineThresholdWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // Z_LOGLINETHRESHOLDWID_H
