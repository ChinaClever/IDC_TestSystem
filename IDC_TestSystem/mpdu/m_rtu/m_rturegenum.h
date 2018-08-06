#ifndef M_RTUREGENUM_H
#define M_RTUREGENUM_H

enum BUS_SetCmdEnum {
    M_RtuReg_LineData = 0,
    M_RtuReg_LineSize = 17-M_RtuReg_LineData+1,

    M_RtuReg_OutputData = 18,
    M_RtuReg_OutputSize = 65-M_RtuReg_OutputData+1,

    M_RtuReg_OutputEles = 66,
    M_RtuReg_OutputEleSize = 137-M_RtuReg_OutputEles+1,

    M_RtuReg_EnvData = 141,
    M_RtuReg_EnvSize = 144-M_RtuReg_EnvData+1,

    M_RtuReg_LineThresholdData = 145,
    M_RtuReg_LineThresholdSize = 156-M_RtuReg_LineThresholdData+1,

    M_RtuReg_OutputThresholdData = 157,
    M_RtuReg_OutputThresholdSize = 252-M_RtuReg_OutputThresholdData+1,

    M_RtuReg_LineSw = 287,
    M_RtuReg_LineSwSize = 289-M_RtuReg_LineSw+1,

    M_RtuReg_EnvThresholdData = 323,
    M_RtuReg_EnvThresholdSize = 330-M_RtuReg_EnvThresholdData+1,

    M_RtuReg_DevAddr = 332,
    M_RtuReg_DevAddrSize = 338-M_RtuReg_DevAddr+1,

    M_RtuReg_LineNum = 331,
    M_RtuReg_LineNumSize = 331-M_RtuReg_LineNum+1,

    M_RtuReg_OutputSw = 339,
    M_RtuReg_OutputSwSize = 387-M_RtuReg_OutputSw+1,

};

#endif // M_RTUREGENUM_H
