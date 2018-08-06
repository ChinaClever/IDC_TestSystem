#include "m_dbenv.h"

M_DbEnv::M_DbEnv()
{
    createTable();
}

M_DbEnv *M_DbEnv::bulid()
{
    static M_DbEnv* sington = nullptr;
    if(sington == nullptr)
        sington = new M_DbEnv();
    return sington;
}
