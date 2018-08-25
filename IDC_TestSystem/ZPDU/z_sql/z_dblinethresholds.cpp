/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_dblinethresholds.h"

Z_DbLineThresholds::Z_DbLineThresholds()
{
    createTable();
}


Z_DbLineThresholds *Z_DbLineThresholds::bulid()
{
    static Z_DbLineThresholds* sington = nullptr;
    if(sington == nullptr)
        sington = new Z_DbLineThresholds();
    return sington;
}

