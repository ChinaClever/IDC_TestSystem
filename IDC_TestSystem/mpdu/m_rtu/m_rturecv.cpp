/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_rturecv.h"

M_RtuRecv::M_RtuRecv()
{

}

bool M_RtuRecv::rtuRecvCrc(uchar *buf, int len, M_sRtuRecv *msg)
{
    bool ret = true;
    int rtn = len-2; uchar *ptr = buf+rtn;

    msg->crc = (ptr[1]*256) + ptr[0]; // 获取校验码
    ushort crc = rtu_crc(buf, rtn);
    if(crc != msg->crc) {
        ret = false;
        qDebug() << "M_RtuRecv rtu recv crc Err!";
    }

    return ret;
}

int M_RtuRecv::rtuRecvHead(uchar *ptr,  M_sRtuRecv *pkt)
{
    pkt->addr = *(ptr++);// 从机地址码
    pkt->fn = *(ptr++);  /*功能码*/
    pkt->len = (*ptr); /*数据长度*/
    if(pkt->len > SERIAL_LEN) pkt->len = 0;

    return 3;
}



bool M_RtuRecv::rtuRecvPacket(uchar *buf, int len, M_sRtuRecv *pkt)
{
    bool ret = false;

//    int line = rtu_recv_len(buf, len);
//    if(line > 0) {
//        uchar *ptr=buf;
//        ptr += rtu_recv_head(ptr, pkt);
//        if(line > 1) {
//            ptr += rtu_recv_dataV3(ptr, &(pkt->data));
//        } else {
//            ptr += rtu_recv_data(ptr, &(pkt->data));
//        }

//        pkt->v = line;
//        ret = rtu_recv_crc(buf, len, pkt);
//    }

    return ret;
}



bool M_RtuRecv::recvPacket(uchar *buf, int len, M_sRtuRecv *pkt)
{
    bool ret = false;
    if((len > 2) && (len < 1024)) {
        ret =  rtuRecvCrc(buf, len, pkt);
        if(ret) {
            ret = rtuRecvPacket(buf, len, pkt);
        }
    } else {
        qDebug() << "M_RtuRecv recvPacket err" << ret;
    }

    return ret;
}
