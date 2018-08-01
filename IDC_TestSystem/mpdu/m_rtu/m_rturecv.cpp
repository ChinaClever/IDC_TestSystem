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

//static bool rtu_recv_packet(uchar *buf, int len, IP_Rtu_Recv *pkt)
//{
//    bool ret = false;

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

//    return ret;
//}



//bool M_RtuRecv::recvPacket(uchar *buf, int len, IP_Rtu_Recv *pkt)
//{
//    bool ret = false;
//    if((len > 2) && (len < 1024))
//        ret = rtu_recv_packet(buf, len, pkt);
//    else
//        qDebug() << "M_RtuRecv recvPacket err" << ret;

//    return ret;
//}
