/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_dblinerecords.h"

Z_DbLineRecords::Z_DbLineRecords()
{
    createTable();
}

Z_DbLineRecords *Z_DbLineRecords::bulid()
{
    static Z_DbLineRecords* sington = nullptr;
    if(sington == nullptr)
        sington = new Z_DbLineRecords();
    return sington;
}

