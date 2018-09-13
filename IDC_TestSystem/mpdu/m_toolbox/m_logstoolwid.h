#ifndef M_LOGSTOOLWID_H
#define M_LOGSTOOLWID_H

#include "m_com/m_datapackets.h"
#include "toolbox/logstoolwid.h"

class M_LogsToolWid : public LogsToolWid
{
    Q_OBJECT

public:
    explicit M_LogsToolWid(QWidget *parent = 0);
};

#endif // M_LOGSTOOLWID_H
