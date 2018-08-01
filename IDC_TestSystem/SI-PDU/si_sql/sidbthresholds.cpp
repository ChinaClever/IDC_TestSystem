/*
 * 阈值信息数据表
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "sidbthresholds.h"

SiDbThresholds::SiDbThresholds()
{
    createTable();
}


SiDbThresholds *SiDbThresholds::bulid()
{
    static SiDbThresholds* sington = nullptr;
    if(sington == nullptr)
        sington = new SiDbThresholds();
    return sington;
}

