/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ipdbmodbuscmd.h"

IpDbModbusCmd::IpDbModbusCmd()
{
   createTable();
}

IpDbModbusCmd *IpDbModbusCmd::bulid()
{
    static IpDbModbusCmd* sington = nullptr;
    if(sington == nullptr)
        sington = new IpDbModbusCmd();
    return sington;
}
