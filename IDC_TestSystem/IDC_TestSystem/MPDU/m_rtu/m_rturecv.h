#ifndef M_RTURECV_H
#define M_RTURECV_H
#include "m_rtusent.h"
#include "rtuzmrecv.h"

class M_RtuRecv : public RtuZmRecv
{
public:
    M_RtuRecv();

protected:
    void devTypeData(uchar *buf, int len, ZM_sRtuPacket &pkt);
};

#endif // M_RTURECV_H
