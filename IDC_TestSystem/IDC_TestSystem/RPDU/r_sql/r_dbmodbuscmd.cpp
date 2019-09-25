/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_dbmodbuscmd.h"

R_DbModbusCmd::R_DbModbusCmd()
{
    createTable();
}

R_DbModbusCmd *R_DbModbusCmd::bulid()
{
    static R_DbModbusCmd* sington = nullptr;
    if(sington == nullptr)
        sington = new R_DbModbusCmd();
    return sington;
}

