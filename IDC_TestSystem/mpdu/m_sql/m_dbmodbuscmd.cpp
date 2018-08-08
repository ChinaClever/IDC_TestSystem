/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_dbmodbuscmd.h"

M_DbModbusCmd::M_DbModbusCmd()
{
    createTable();
}

M_DbModbusCmd *M_DbModbusCmd::bulid()
{
    static M_DbModbusCmd* sington = nullptr;
    if(sington == nullptr)
        sington = new M_DbModbusCmd();
    return sington;
}
