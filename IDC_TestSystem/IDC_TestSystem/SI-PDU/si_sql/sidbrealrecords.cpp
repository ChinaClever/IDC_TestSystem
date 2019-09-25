/*
 * 实时信息数据表
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "sidbrealrecords.h"

SiDbRealRecords::SiDbRealRecords()
{    
    createTable();
}


SiDbRealRecords *SiDbRealRecords::bulid()
{
    static SiDbRealRecords* sington = nullptr;
    if(sington == nullptr)
        sington = new SiDbRealRecords();
    return sington;
}

