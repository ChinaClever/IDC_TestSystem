/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_logstoolwid.h"

Z_LogsToolWid::Z_LogsToolWid(QWidget *parent) :  LogsToolWid(parent)
{
    config = Z_ConfigFile::bulid();
}

