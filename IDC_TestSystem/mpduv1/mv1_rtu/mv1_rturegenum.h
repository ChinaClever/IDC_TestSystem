#ifndef MV1_RTUREGENUM_H
#define MV1_RTUREGENUM_H

enum MV1_SetCmdEnum {
    MV1_RtuReg_LineData = 0,
    MV1_RtuReg_LineSize = 17-MV1_RtuReg_LineData+1,

    MV1_RtuReg_OutputData = 18,
    MV1_RtuReg_OutputSize = 65-MV1_RtuReg_OutputData+1,

    MV1_RtuReg_OutputEles = 66,
    MV1_RtuReg_OutputEleSize = 137-MV1_RtuReg_OutputEles+1,

    MV1_RtuReg_OutputSw = 138,
    MV1_RtuReg_OutputSwSize = 140-MV1_RtuReg_OutputSw+1,

    MV1_RtuReg_EnvData = 141,
    MV1_RtuReg_EnvSize = 144-MV1_RtuReg_EnvData+1,

    MV1_RtuReg_LineThresholdData = 145,
    MV1_RtuReg_LineThresholdSize = 156-MV1_RtuReg_LineThresholdData+1,

    MV1_RtuReg_OutputThresholdData = 157,
    MV1_RtuReg_OutputThresholdSize = 252-MV1_RtuReg_OutputThresholdData+1,

    MV1_RtuReg_LineSw = 287,
    MV1_RtuReg_LineSwSize = 295-MV1_RtuReg_LineSw+1,

    MV1_RtuReg_EnvThresholdData = 323,
    MV1_RtuReg_EnvThresholdSize = 330-MV1_RtuReg_EnvThresholdData+1,

    MV1_RtuReg_DevAddr = 332,
    MV1_RtuReg_DevAddrSize = 338-MV1_RtuReg_DevAddr+1,

    MV1_RtuReg_LineNum = 331,
    MV1_RtuReg_LineNumSize = 331-MV1_RtuReg_LineNum+1,

};

#endif // MV1_RTUREGENUM_H
