/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_dbenv.h"

Z_DbEnv::Z_DbEnv()
{
    createTable();
}

Z_DbEnv *Z_DbEnv::bulid()
{
    static Z_DbEnv* sington = nullptr;
    if(sington == nullptr)
        sington = new Z_DbEnv();
    return sington;
}
