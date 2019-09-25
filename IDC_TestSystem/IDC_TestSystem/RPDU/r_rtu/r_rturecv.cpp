/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_rturecv.h"

extern ushort rtu_crc(uchar *buf, int len);

ushort *r_reg_array(int id)
{
    static ushort array[R_RtuReg_CmdNum][2] = {
        R_RtuReg_OutputCur,       R_RtuReg_OutputCurSize,
        R_RtuReg_OutputCurMin,         R_RtuReg_OutputCurMinSize,
        R_RtuReg_OutputCurMax,        R_RtuReg_OutputCurMaxSize,
        R_RtuReg_LineCurMin,     R_RtuReg_LineCurMinSize,
        R_RtuReg_LineCurMax,      R_RtuReg_LineCurMaxSize,

        R_RtuReg_LineVolMin,        R_RtuReg_LineVolMinSize,
        R_RtuReg_LineVolMax,     R_RtuReg_LineVolMaxSize,
        R_RtuReg_LineCur,     R_RtuReg_LineCurSize,
        R_RtuReg_LineVol,   R_RtuReg_LineVolSize,

        R_RtuReg_TemMin,   R_RtuReg_TemMinSize,
        R_RtuReg_HumMin,        R_RtuReg_HumMinSize,
        R_RtuReg_TemMax,        R_RtuReg_TemMaxSize,
        R_RtuReg_HumMax,        R_RtuReg_HumMaxSize,
        R_RtuReg_TemData,        R_RtuReg_TemDataSize,
        R_RtuReg_HumData,        R_RtuReg_HumDataSize,

        R_RtuReg_WaterData ,        R_RtuReg_WaterSize,
        R_RtuReg_SmokeData ,        R_RtuReg_SmokeSize,
        R_RtuReg_DoorData ,        R_RtuReg_DoorSize,

        R_RtuReg_OutputEle ,        R_RtuReg_OutputEleSize ,
        R_RtuReg_LinePF ,        R_RtuReg_LinePFSize ,
        R_RtuReg_LineEle ,        R_RtuReg_LineEleSize ,
        R_RtuReg_OutputSw ,        R_RtuReg_OutputSwSize ,
        R_RtuReg_OutputNum ,        R_RtuReg_OutputNumSize ,

        R_RtuReg_DevType ,        R_RtuReg_DevTypeSize ,

        R_RtuReg_SlaveNum ,        R_RtuReg_SlaveNumSize ,

    };

    return array[id];
}

R_RtuRecv::R_RtuRecv()
{

}

void R_RtuRecv::devTypeData(uchar *buf, int len, ZM_sRtuPacket &pkt)
{  //1-A:1 1-B:2 1-C:3 1-D:4
    //2-A:5 2-B:6 2-C:7 2-D:8
    //3-A:9 3-B:10 3-C:11 3-D:12
    ushort array[3] = {0};
    rtuRecvData(buf, len, array);

    int value = array[0], line = 3;
    if(value < 5) line = 1;
    else if(value >= 5 && value < 9) line = 2;

    pkt.line.num = line;
    pkt.devSpec = value%4;
}

bool R_RtuRecv::rtuRecvPacket(uchar *buf, int len, ushort reg, ZM_sRtuPacket &pkt)
{
    bool ret = true;
    ushort *ptrShort = nullptr;
    uint *ptrInt = nullptr;

    switch (reg) {
    case R_RtuReg_DevType: devTypeData(buf, len, pkt);break;
    case R_RtuReg_OutputNum: ptrShort = &(pkt.output.num); break;
    case R_RtuReg_OutputSw: ptrShort = pkt.output.sw;break;

    case R_RtuReg_LineCur: ptrShort = pkt.line.cur.value; break;
    case R_RtuReg_LineCurMin: ptrShort = pkt.line.cur.min; break;
    case R_RtuReg_LineCurMax: ptrShort = pkt.line.cur.max; break;

    case R_RtuReg_LineVol: ptrShort = pkt.line.vol.value; break;
    case R_RtuReg_LineVolMin: ptrShort = pkt.line.vol.min; break;
    case R_RtuReg_LineVolMax: ptrShort = pkt.line.vol.max; break;

    case R_RtuReg_LineEle: ptrShort = pkt.line.ele; ptrInt = (uint * )pkt.line.ele;break;
    case R_RtuReg_LinePF: ptrShort = pkt.line.pf; break;

    case R_RtuReg_OutputCur: ptrShort = pkt.output.cur.value; break;
    case R_RtuReg_OutputCurMin: ptrShort = pkt.output.cur.min; break;
    case R_RtuReg_OutputCurMax: ptrShort = pkt.output.cur.max; break;
    case R_RtuReg_OutputEle: ptrShort = pkt.output.ele; ptrInt = (uint * )pkt.output.ele;break;

    case R_RtuReg_TemData: ptrShort = pkt.env.tem.value; break;
    case R_RtuReg_TemMin: ptrShort = pkt.env.tem.min; break;
    case R_RtuReg_TemMax: ptrShort = pkt.env.tem.max; break;

    case R_RtuReg_HumData: ptrShort = pkt.env.hum.value; break;
    case R_RtuReg_HumMin: ptrShort = pkt.env.hum.min; break;
    case R_RtuReg_HumMax: ptrShort = pkt.env.hum.max; break;

    case R_RtuReg_DoorData: ptrShort = pkt.env.door; break;
    case R_RtuReg_WaterData: ptrShort = pkt.env.water; break;
    case R_RtuReg_SmokeData: ptrShort = pkt.env.smoke; break;

    case R_RtuReg_SlaveNum: break;

    default:
        ret = false;
        //qDebug() << "R_RtuRecv::rtuRecvPacket err" << reg;
        break;
    }

    if(ptrShort&&ptrInt){rtuRecvData(buf, len, ptrInt , ptrShort);}
    else if(ptrShort) {rtuRecvData(buf, len, ptrShort);}

    return ret;
}

bool R_RtuRecv::recvPacket(uchar *buf, int len, ushort reg, ZM_sRtuRecv *pkt)
{
    bool ret = false;
    if((len > 5) && (len < 1024)) {
        ret =  rtuRecvCrc(buf, len, pkt);
        if(ret) {
            int rtn = rtuRecvHead(buf,pkt);
            if(rtn < len)
            {
                buf += 3;
                ret = rtuRecvPacket(buf, rtn, reg, pkt->data);
            }
        }
    } else {
        qDebug() << "Rpdu_RtuRecv recvPacket err" << ret;
    }

    return ret;
}
