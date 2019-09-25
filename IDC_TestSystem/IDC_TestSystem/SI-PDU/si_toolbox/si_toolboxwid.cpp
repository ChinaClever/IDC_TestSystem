/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "si_toolboxwid.h"

SI_ToolBoxWid::SI_ToolBoxWid(QWidget *parent) : ToolBoxWid(parent)
{
    mConfig = SiConfigFile::bulid();
    mModeToolWid = new SI_ModeToolWid();
    mStatusToolWid = new SI_StatusToolWid();
    mLogsToolWid = new SI_LogsToolWid();
    mSettingToolWid = new SI_SettingToolWid();
}
