/*
 * 命令数据表
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "sidbmodbuscmd.h"

SiDbModbusCmd::SiDbModbusCmd()
{    
    createTable();
}


SiDbModbusCmd *SiDbModbusCmd::bulid()
{
    static SiDbModbusCmd* sington = nullptr;
    if(sington == nullptr)
        sington = new SiDbModbusCmd();
    return sington;
}
