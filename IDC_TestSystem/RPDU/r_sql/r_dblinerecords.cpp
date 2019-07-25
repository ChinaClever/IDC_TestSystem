/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_dblinerecords.h"

R_DbLineRecords::R_DbLineRecords()
{
    createTable();
}

R_DbLineRecords *R_DbLineRecords::bulid()
{
    static R_DbLineRecords* sington = nullptr;
    if(sington == nullptr)
        sington = new R_DbLineRecords();
    return sington;
}

