﻿/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_settingtoolwid.h"

IP_SettingToolWid::IP_SettingToolWid(QWidget *parent) : SettingToolWid(parent)
{
    config = IP_ConfigFile::bulid();
    ippdu(false);
    initVersion();
}


