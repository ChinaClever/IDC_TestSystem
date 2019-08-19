/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_dbenv.h"

R_DbEnv::R_DbEnv()
{
    createTable();
}

R_DbEnv *R_DbEnv::bulid()
{
    static R_DbEnv* sington = nullptr;
    if(sington == nullptr)
        sington = new R_DbEnv();
    return sington;
}
