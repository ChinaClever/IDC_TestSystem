#ifndef SI_RTU_SETCMD_H
#define SI_RTU_SETCMD_H

enum SI_SetCmdEnum {
    SI_Addr_CMD = 0x1001, //PDU地址
    SI_MaxVol1_CMD,   // 设置升压超限报警L1
    SI_MinVol1_CMD,   // 设置欠压超限报警L1
    SI_MaxVol2_CMD,   // 设置升压超限报警L2
    SI_MinVol2_CMD,   // 设置欠压超限报警L2
    SI_MaxVol3_CMD,   // 设置升压超限报警L3
    SI_MinVol3_CMD,   // 设置欠压超限报警L3

    SI_MaxCur1_CMD,   // 设置电流上限报警L1
    SI_MinCur1_CMD,   // 设置电流下限报警L1
    SI_MaxCur2_CMD,   // 设置电流上限报警L2
    SI_MinCur2_CMD,   // 设置电流下限报警L2
    SI_MaxCur3_CMD,   // 设置电流上限报警L3
    SI_MinCur3_CMD,   // 设置电流下限报警L3

    SI_MaxTem_CMD,   // 设置温度上限报警值
    SI_MinTem_CMD,   // 设置温度下限报警值2
    SI_MaxHum_CMD,   // 设置湿度度上限报警值
    SI_MinHum_CMD,   // 设置湿度下限报警值

    SI_BR_CMD, // 设置波特率（01为4800，02为9600，03为19200，04为38400）
    SI_ELE_CMD, // 电能值清零 （1111 0000自左往右依次为第一至第二、第三相和直流）
};

#endif // SI_RTU_SETCMD_H
