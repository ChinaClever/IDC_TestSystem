/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_modetoolwid.h"

Z_ModeToolWid::Z_ModeToolWid(QWidget *parent) :  ModeToolWid(parent)
{
    mConfig = Z_ConfigFile::bulid();
}

