/*
 * Si 设备阈值实时显示表格
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_thresholdtablewid.h"

SI_ThresholdTableWid::SI_ThresholdTableWid(QWidget *parent) : LineThresholdTableWid(parent)
{
    mPackets = SIDataPackets::bulid()->packets;
}
