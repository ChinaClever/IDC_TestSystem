/*
 * Si 环境信息实时显示表格
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_envtablewid.h"


SI_EnvTableWid::SI_EnvTableWid(QWidget *parent) : EnvTableWid(parent)
{
    mPackets = SIDataPackets::bulid()->packets;
}
