/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_dbmodbuscmd.h"

MV1_DbModbusCmd::MV1_DbModbusCmd()
{
    createTable();
}

MV1_DbModbusCmd *MV1_DbModbusCmd::bulid()
{
    static MV1_DbModbusCmd* sington = nullptr;
    if(sington == nullptr)
        sington = new MV1_DbModbusCmd();
    return sington;
}
