#ifndef R_SETTINGTOOLWID_H
#define R_SETTINGTOOLWID_H

#include "r_com/r_datapackets.h"
#include "toolbox/toolboxwid.h"

class R_SettingToolWid : public SettingToolWid
{
    Q_OBJECT

public:
    explicit R_SettingToolWid(QWidget *parent = 0);
};

#endif // R_SETTINGTOOLWID_H
