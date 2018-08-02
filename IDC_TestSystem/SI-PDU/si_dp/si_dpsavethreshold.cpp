/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "si_dpsavethreshold.h"

SI_DpSaveThreshold::SI_DpSaveThreshold(QObject *parent) : DpSaveLineThreshold(parent)
{
    mPackets = SIDataPackets::bulid()->packets;
}
