/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_settingtoolwid.h"

M_SettingToolWid::M_SettingToolWid(QWidget *parent) : SettingToolWid(parent)
{
    config = M_ConfigFile::bulid();
}
