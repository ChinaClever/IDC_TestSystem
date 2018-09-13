#include "si_modetoolwid.h"

SI_ModeToolWid::SI_ModeToolWid(QWidget *parent) : ModeToolWid(parent)
{
    mConfig = SiConfigFile::bulid();
    sipdu();
}
