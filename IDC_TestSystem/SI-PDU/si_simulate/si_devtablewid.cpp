/*
 * Si 设备信息实时显示表格
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_devtablewid.h"

SI_DevTableWid::SI_DevTableWid(QWidget *parent) : LineTableWid(parent)
{
    mPackets = SIDataPackets::bulid()->packets;
}
