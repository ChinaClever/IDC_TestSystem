/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_dblooprecords.h"

Z_DbLoopRecords::Z_DbLoopRecords()
{
    createTable();
}

Z_DbLoopRecords *Z_DbLoopRecords::bulid()
{
    static Z_DbLoopRecords* sington = nullptr;
    if(sington == nullptr)
        sington = new Z_DbLoopRecords();
    return sington;
}

