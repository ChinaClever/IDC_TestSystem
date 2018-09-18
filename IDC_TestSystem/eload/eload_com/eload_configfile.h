#ifndef ELOAD_CONFIGFILE_H
#define ELOAD_CONFIGFILE_H
#include "configbase.h"

enum {
    ELoad_Test_Stop,
    ELoad_Test_Simulate,  // 模拟测试
    ELoad_Test_Function, // 功能测试

    ELoad_Info_Home, // 母线信息
    ELoad_Info_Trans, // Modbus传输统计实时显示界面
    ELoad_Info_Threshold, // 设备阈值实时显示界面
    ELoad_Info_Env, // 环境信息_
    ELoad_Info_Loop,
    ELoad_Info_LoopThreshold,
    ELoad_Info_Input,
    ELoad_Info_InputThreshold,
    ELoad_Info_Set,

    ELoad_Log_Modbus, // Modbus日志界面
    ELoad_Log_Trans, // Modbus 传输日志
    ELoad_Log_Env,  //设备环境日志
    ELoad_Log_Records, // 设备纪录日志
    ELoad_Log_Threshold, // 设备阈值日志
    ELoad_Log_Loop,
    ELoad_Log_Output,
    ELoad_Log_Alarm,

    ELoad_Tem_RiseOne,
    ELoad_Tem_RiseTwo,
    ELoad_Tem_RiseThree,
};


class ELoad_ConfigFile: public ConfigBase
{
    ELoad_ConfigFile();
public:
    static ELoad_ConfigFile *bulid();
    QString getPrefix(){return "eload";}
};

#endif // ELOAD_CONFIGFILE_H
