/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_modetoolwid.h"

M_ModeToolWid::M_ModeToolWid(QWidget *parent) : ModeToolWid(parent)
{
    mConfig = M_ConfigFile::bulid();
}
