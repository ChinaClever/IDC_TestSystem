#ifndef MV1_LOGSTOOLWID_H
#define MV1_LOGSTOOLWID_H

#include "mv1_com/mv1_datapackets.h"
#include "toolbox/toolboxwid.h"

class MV1_LogsToolWid : public LogsToolWid
{
    Q_OBJECT

public:
    explicit MV1_LogsToolWid(QWidget *parent = 0);
};

#endif // MV1_LOGSTOOLWID_H
