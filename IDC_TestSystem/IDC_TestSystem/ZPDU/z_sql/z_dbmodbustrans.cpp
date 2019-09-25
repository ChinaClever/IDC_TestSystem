/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_dbmodbustrans.h"

Z_DbModbusTrans::Z_DbModbusTrans()
{
    createTable();
}

Z_DbModbusTrans *Z_DbModbusTrans::bulid()
{
    static Z_DbModbusTrans* sington = nullptr;
    if(sington == nullptr)
        sington = new Z_DbModbusTrans();
    return sington;
}

