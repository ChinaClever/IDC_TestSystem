/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_dboutputrecords.h"

Z_DbOutputRecords::Z_DbOutputRecords()
{
    createTable();
}

Z_DbOutputRecords *Z_DbOutputRecords::bulid()
{
    static Z_DbOutputRecords* sington = nullptr;
    if(sington == nullptr)
        sington = new Z_DbOutputRecords();
    return sington;
}
