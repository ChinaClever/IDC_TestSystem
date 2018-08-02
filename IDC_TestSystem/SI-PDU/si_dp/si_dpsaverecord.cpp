/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "si_dpsaverecord.h"

SI_DpSaveRecord::SI_DpSaveRecord(QObject *parent) : DpSaveLine(parent)
{
    mPackets = SIDataPackets::bulid()->packets;
}
