/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_dblinethresholds.h"

M_DbLineThresholds::M_DbLineThresholds()
{
    createTable();
}


M_DbLineThresholds *M_DbLineThresholds::bulid()
{
    static M_DbLineThresholds* sington = nullptr;
    if(sington == nullptr)
        sington = new M_DbLineThresholds();
    return sington;
}
