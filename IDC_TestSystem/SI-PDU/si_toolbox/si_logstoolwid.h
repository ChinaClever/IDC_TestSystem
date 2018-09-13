#ifndef SI_LOGSTOOLWID_H
#define SI_LOGSTOOLWID_H

#include "si_com/sidatapackets.h"
#include "toolbox/logstoolwid.h"

class SI_LogsToolWid : public LogsToolWid
{
    Q_OBJECT
public:
    explicit SI_LogsToolWid(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // SI_LOGSTOOLWID_H
