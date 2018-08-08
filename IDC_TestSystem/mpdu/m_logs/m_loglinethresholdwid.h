#ifndef M_LOGLINETHRESHOLDWID_H
#define M_LOGLINETHRESHOLDWID_H

#include "m_loglinerecordwid.h"

class M_LogLineThresholdWid : public LogComWid
{
    Q_OBJECT
public:
    explicit M_LogLineThresholdWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // M_LOGLINETHRESHOLDWID_H
