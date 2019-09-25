/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_toolboxwid.h"

Z_ToolBoxWid::Z_ToolBoxWid(QWidget *parent) :  ToolBoxWid(parent)
{
    mConfig = Z_ConfigFile::bulid();
    mModeToolWid = new Z_ModeToolWid();
    mStatusToolWid = new Z_StatusToolWid();
    mLogsToolWid = new Z_LogsToolWid();
    mSettingToolWid = new Z_SettingToolWid();
}
