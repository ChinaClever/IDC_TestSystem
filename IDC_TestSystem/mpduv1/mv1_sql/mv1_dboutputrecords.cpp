/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_dboutputrecords.h"

MV1_DbOutputRecords::MV1_DbOutputRecords()
{
    createTable();
}

MV1_DbOutputRecords *MV1_DbOutputRecords::bulid()
{
    static MV1_DbOutputRecords* sington = nullptr;
    if(sington == nullptr)
        sington = new MV1_DbOutputRecords();
    return sington;
}
