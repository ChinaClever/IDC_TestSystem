#include "z_modetoolwid.h"

Z_ModeToolWid::Z_ModeToolWid(QWidget *parent) :  ModeToolWid(parent)
{
    mConfig = Z_ConfigFile::bulid();
}

