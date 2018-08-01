/*
 * 环境数据表
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "sidbenv.h"

SiDbEnv::SiDbEnv()
{
    createTable();
}


SiDbEnv *SiDbEnv::bulid()
{
    static SiDbEnv* sington = nullptr;
    if(sington == nullptr)
        sington = new SiDbEnv();
    return sington;
}

