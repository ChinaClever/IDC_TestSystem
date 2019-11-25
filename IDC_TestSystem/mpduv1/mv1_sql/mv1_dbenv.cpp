/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_dbenv.h"

MV1_DbEnv::MV1_DbEnv()
{
    createTable();
}

MV1_DbEnv *MV1_DbEnv::bulid()
{
    static MV1_DbEnv* sington = nullptr;
    if(sington == nullptr)
        sington = new MV1_DbEnv();
    return sington;
}
