/*
 * 数据库
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "sidbmodbustrans.h"

SiDbModbusTrans::SiDbModbusTrans()
{
    createTable();
}


SiDbModbusTrans *SiDbModbusTrans::bulid()
{
    static SiDbModbusTrans* sington = nullptr;
    if(sington == nullptr)
        sington = new SiDbModbusTrans();
    return sington;
}

