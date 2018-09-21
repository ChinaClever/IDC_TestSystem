#ifndef Z_SETTINGTOOLWID_H
#define Z_SETTINGTOOLWID_H

#include "z_com/z_datapackets.h"
#include "toolbox/toolboxwid.h"

class Z_SettingToolWid : public SettingToolWid
{
    Q_OBJECT

public:
    explicit Z_SettingToolWid(QWidget *parent = 0);
};

#endif // Z_SETTINGTOOLWID_H
