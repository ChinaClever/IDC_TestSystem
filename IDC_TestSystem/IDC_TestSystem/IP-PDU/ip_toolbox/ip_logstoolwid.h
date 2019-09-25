#ifndef IP_LOGSTOOLWID_H
#define IP_LOGSTOOLWID_H

#include "ip_com/ipdatapackets.h"
#include "toolbox/toolboxwid.h"

class IP_LogsToolWid : public LogsToolWid
{
    Q_OBJECT

public:
    explicit IP_LogsToolWid(QWidget *parent = 0);
};

#endif // IP_LOGSTOOLWID_H
