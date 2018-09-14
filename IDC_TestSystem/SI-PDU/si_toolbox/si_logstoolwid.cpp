/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "si_logstoolwid.h"

SI_LogsToolWid::SI_LogsToolWid(QWidget *parent) : LogsToolWid(parent)
{
    config = SiConfigFile::bulid();
    sipdu();
}
