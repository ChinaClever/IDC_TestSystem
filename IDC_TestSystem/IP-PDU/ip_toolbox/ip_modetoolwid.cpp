#include "ip_modetoolwid.h"

IP_ModeToolWid::IP_ModeToolWid(QWidget *parent) : ModeToolWid(parent)
{
    mConfig = IP_ConfigFile::bulid();
}
