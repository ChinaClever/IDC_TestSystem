#include "m_modetoolwid.h"

M_ModeToolWid::M_ModeToolWid(QWidget *parent) : ModeToolWid(parent)
{
    mConfig = M_ConfigFile::bulid();
}
