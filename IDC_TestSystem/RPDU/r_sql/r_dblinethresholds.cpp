/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_dblinethresholds.h"

R_DbLineThresholds::R_DbLineThresholds()
{
    createTable();
}


R_DbLineThresholds *R_DbLineThresholds::bulid()
{
    static R_DbLineThresholds* sington = nullptr;
    if(sington == nullptr)
        sington = new R_DbLineThresholds();
    return sington;
}

