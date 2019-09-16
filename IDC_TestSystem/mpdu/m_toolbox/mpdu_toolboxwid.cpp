/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mpdu_toolboxwid.h"

MPDU_ToolBoxWid::MPDU_ToolBoxWid(QWidget *parent) : ToolBoxWid(parent)
{
    mConfig = M_ConfigFile::bulid();
    mModeToolWid = new M_ModeToolWid();
    mStatusToolWid = new M_StatusToolWid();
    mLogsToolWid = new M_LogsToolWid();
    mSettingToolWid = new M_SettingToolWid();
}

