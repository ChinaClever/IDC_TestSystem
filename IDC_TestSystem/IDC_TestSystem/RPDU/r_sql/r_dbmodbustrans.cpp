/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_dbmodbustrans.h"

R_DbModbusTrans::R_DbModbusTrans()
{
    createTable();
}

R_DbModbusTrans *R_DbModbusTrans::bulid()
{
    static R_DbModbusTrans* sington = nullptr;
    if(sington == nullptr)
        sington = new R_DbModbusTrans();
    return sington;
}

