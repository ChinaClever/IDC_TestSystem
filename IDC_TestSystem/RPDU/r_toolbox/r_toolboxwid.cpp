/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_toolboxwid.h"

R_ToolBoxWid::R_ToolBoxWid(QWidget *parent) :  ToolBoxWid(parent)
{
    mModeToolWid = new R_ModeToolWid();
    mStatusToolWid = new R_StatusToolWid();
    mLogsToolWid = new R_LogsToolWid();
    mSettingToolWid = new R_SettingToolWid();
    mConfig = R_ConfigFile::bulid();

}
