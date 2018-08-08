/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_dblinerecords.h"

M_DbLineRecords::M_DbLineRecords()
{
    createTable();
}

M_DbLineRecords *M_DbLineRecords::bulid()
{
    static M_DbLineRecords* sington = nullptr;
    if(sington == nullptr)
        sington = new M_DbLineRecords();
    return sington;
}
