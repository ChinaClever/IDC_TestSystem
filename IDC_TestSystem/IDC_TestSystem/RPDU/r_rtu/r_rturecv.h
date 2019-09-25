#ifndef R_RTURECV_H
#define R_RTURECV_H
#include "r_rtusent.h"
#include "rtuzmrecv.h"
#include "r_rturegenum.h"

class R_RtuRecv : public RtuZmRecv
{
public:
    R_RtuRecv();
public:
    virtual void devTypeData(uchar *buf, int len, ZM_sRtuPacket &pkt);
    bool rtuRecvPacket(uchar *buf, int len, ushort reg, ZM_sRtuPacket &pkt);
    bool recvPacket(uchar *buf, int len, ushort reg, ZM_sRtuRecv *pkt);
};
ushort *r_reg_array(int id);
#endif // R_RTURECV_H
