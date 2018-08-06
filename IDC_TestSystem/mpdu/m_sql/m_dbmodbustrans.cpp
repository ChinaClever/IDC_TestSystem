#include "m_dbmodbustrans.h"

M_DbModbusTrans::M_DbModbusTrans()
{
    createTable();
}

M_DbModbusTrans *M_DbModbusTrans::bulid()
{
    static M_DbModbusTrans* sington = nullptr;
    if(sington == nullptr)
        sington = new M_DbModbusTrans();
    return sington;
}
