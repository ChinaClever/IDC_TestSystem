/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mpduv1_toolboxwid.h"

MPDUV1_ToolBoxWid::MPDUV1_ToolBoxWid(QWidget *parent) : ToolBoxWid(parent)
{
    mConfig = MV1_ConfigFile::bulid();
    mModeToolWid = new MV1_ModeToolWid();
    mStatusToolWid = new MV1_StatusToolWid();
    mLogsToolWid = new MV1_LogsToolWid();
    mSettingToolWid = new MV1_SettingToolWid();
}

