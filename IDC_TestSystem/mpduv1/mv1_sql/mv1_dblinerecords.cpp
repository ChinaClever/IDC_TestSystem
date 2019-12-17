/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_dblinerecords.h"

MV1_DbLineRecords::MV1_DbLineRecords()
{
    createTable();
}

MV1_DbLineRecords *MV1_DbLineRecords::bulid()
{
    static MV1_DbLineRecords* sington = nullptr;
    if(sington == nullptr)
        sington = new MV1_DbLineRecords();
    return sington;
}
