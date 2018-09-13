#include "si_settingtoolwid.h"

SI_SettingToolWid::SI_SettingToolWid(QWidget *parent) : SettingToolWid(parent)
{
    config = SiConfigFile::bulid();
}
