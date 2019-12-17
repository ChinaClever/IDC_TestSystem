/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_dblinethresholds.h"

MV1_DbLineThresholds::MV1_DbLineThresholds()
{
    createTable();
}


MV1_DbLineThresholds *MV1_DbLineThresholds::bulid()
{
    static MV1_DbLineThresholds* sington = nullptr;
    if(sington == nullptr)
        sington = new MV1_DbLineThresholds();
    return sington;
}
