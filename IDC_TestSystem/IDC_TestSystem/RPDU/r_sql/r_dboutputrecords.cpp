/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_dboutputrecords.h"

R_DbOutputRecords::R_DbOutputRecords()
{
    createTable();
}

R_DbOutputRecords *R_DbOutputRecords::bulid()
{
    static R_DbOutputRecords* sington = nullptr;
    if(sington == nullptr)
        sington = new R_DbOutputRecords();
    return sington;
}
