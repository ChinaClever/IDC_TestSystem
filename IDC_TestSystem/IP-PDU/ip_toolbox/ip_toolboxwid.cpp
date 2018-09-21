/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_toolboxwid.h"

IP_ToolBoxWid::IP_ToolBoxWid(QWidget *parent) :  ToolBoxWid(parent)
{
    mModeToolWid = new IP_ModeToolWid();
    mStatusToolWid = new IP_StatusToolWid();
    mLogsToolWid = new IP_LogsToolWid();
    mSettingToolWid = new IP_SettingToolWid();
    mConfig = IP_ConfigFile::bulid();
}

