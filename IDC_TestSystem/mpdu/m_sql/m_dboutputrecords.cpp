/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_dboutputrecords.h"

M_DbOutputRecords::M_DbOutputRecords()
{
    createTable();
}

M_DbOutputRecords *M_DbOutputRecords::bulid()
{
    static M_DbOutputRecords* sington = nullptr;
    if(sington == nullptr)
        sington = new M_DbOutputRecords();
    return sington;
}
