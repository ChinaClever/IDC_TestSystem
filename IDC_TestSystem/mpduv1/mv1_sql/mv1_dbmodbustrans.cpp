/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_dbmodbustrans.h"

MV1_DbModbusTrans::MV1_DbModbusTrans()
{
    createTable();
}

MV1_DbModbusTrans *MV1_DbModbusTrans::bulid()
{
    static MV1_DbModbusTrans* sington = nullptr;
    if(sington == nullptr)
        sington = new MV1_DbModbusTrans();
    return sington;
}
