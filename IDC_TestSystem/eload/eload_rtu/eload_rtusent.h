#ifndef ELOAD_RTUSENT_H
#define ELOAD_RTUSENT_H
#include <QtCore>

enum {
    ELoad_FN_Set = 0x10, //	设置数据参数
    ELoad_FN_Ctr = 0x11, //	电位器单个动态控制
    ELoad_FN_AllCtr = 0x12, //	电位器全部动态控制
    ELoad_FN_SW = 0XA1, //	继电器开关控制
    ELoad_FN_Init = 0XA5, //	初始化
    ELoad_FN_Rest = 0XA6, //	重启
    ELoad_FN_Loop = 0XA7, //	握手命令

    ELoad_DP_1 = 0x0101, //	数字电位器1
    ELoad_DP_2, //	数字电位器2
    ELoad_DP_3, //	数字电位器3
    ELoad_DP_4, //	数字电位器4
    ELoad_DP_5, //	数字电位器5
    ELoad_DP_6, //	数字电位器6
    ELoad_DP_7, //	数字电位器7
    ELoad_DP_8, //	数字电位器8

    ELoad_BR_Reg = 0x0112, //	波特率设置
    ELoad_BR_4800 = 1,
    ELoad_BR_9600 = 2,
    ELoad_BR_19200 = 3,
    ELoad_BR_38400 = 4,
};
extern ushort si_rtu_crc(uchar *buf, int len);

class ELoad_RtuSent
{
public:
    ELoad_RtuSent();

    int loopBack(uchar addr, uchar *buf);
    int restCmd(uchar addr, uchar *buf);
    int initCmd(uchar addr, uchar *buf);

    int setData(uchar addr, ushort reg, ushort value, uchar *buf);
    int setBaudRate(uchar addr, ushort reg, uchar value, uchar *buf);
    int switchCtr(uchar addr,ushort reg, uchar value, uchar *buf);

    int setDpAdjust(uchar addr, ushort reg, ushort start, ushort end, ushort t, uchar *buf );
    int setAllDpAdjust(uchar addr, ushort start, ushort end, ushort t, uchar *buf);

protected:
    ushort rtu_crc(uchar *buf, int len){return si_rtu_crc(buf, len);}
    int setDataBuf(uchar addr, uchar fn, ushort reg, ushort value, uchar *buf);

private:

};

#endif // ELOAD_RTUSENT_H
