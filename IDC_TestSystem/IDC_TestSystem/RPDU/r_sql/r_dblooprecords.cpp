/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_dblooprecords.h"

R_DbLoopRecords::R_DbLoopRecords()
{
    createTable();
}

R_DbLoopRecords *R_DbLoopRecords::bulid()
{
    static R_DbLoopRecords* sington = nullptr;
    if(sington == nullptr)
        sington = new R_DbLoopRecords();
    return sington;
}

