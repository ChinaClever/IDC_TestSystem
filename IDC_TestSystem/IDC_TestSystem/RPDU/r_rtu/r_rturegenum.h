#ifndef R_SETCMDENUM_H
#define R_SETCMDENUM_H


enum R_SetCmdEnum {
    R_RtuReg_OutputCur = 0,//0 BD有,AC没有
    R_RtuReg_OutputCurSize = 0x17+1,

    R_RtuReg_OutputCurMin = 0x100,//1 0x100 BD有,AC没有
    R_RtuReg_OutputCurMinSize = 0x17+1,
    R_RtuReg_OutputCurMax = 0x130,//2 0x130 BD有,AC没有
    R_RtuReg_OutputCurMaxSize = 0x17+1,

    R_RtuReg_LineCurMin = 0x200,//3 0x200
    R_RtuReg_LineCurMinSize = 0x02+1,
    R_RtuReg_LineCurMax = 0x203,//4 0x203
    R_RtuReg_LineCurMaxSize = 0x02+1,

    R_RtuReg_LineVolMin = 0x206,//5 0x206
    R_RtuReg_LineVolMinSize = 0x02+1,
    R_RtuReg_LineVolMax = 0x209,//6 0x209
    R_RtuReg_LineVolMaxSize = 0x02+1,

    R_RtuReg_LineCur = 0x20C,//7  0x20C
    R_RtuReg_LineCurSize = 0x02 + 1,
    R_RtuReg_LineVol = 0x20F,//8  0x20F
    R_RtuReg_LineVolSize = 0x02 + 1,

    R_RtuReg_TemMin = 0x300,//9 0x300
    R_RtuReg_TemMinSize = 0x03+1,
    R_RtuReg_HumMin = 0x304,//10 0x304
    R_RtuReg_HumMinSize = 0x03+1,

    R_RtuReg_TemMax = 0x310,//11 0x310
    R_RtuReg_TemMaxSize = 0x03+1,
    R_RtuReg_HumMax = 0x314,//12 0x314
    R_RtuReg_HumMaxSize = 0x03+1,

    R_RtuReg_TemData = 0x320,//13 0x320
    R_RtuReg_TemDataSize = 0x03+1,
    R_RtuReg_HumData = 0x328,//14 0x328
    R_RtuReg_HumDataSize = 0x03+1,


    R_RtuReg_WaterData = 0x400,//15
    R_RtuReg_WaterSize = 0x01,

    R_RtuReg_SmokeData = 0x410,//16
    R_RtuReg_SmokeSize = 0x01,

    R_RtuReg_DoorData = 0x420,//17
    R_RtuReg_DoorSize = 0x02,

    R_RtuReg_OutputEle = 0x500,//18
    R_RtuReg_OutputEleSize = 0x30,//取四个

    R_RtuReg_LinePF = 0x600,//19
    R_RtuReg_LinePFSize = 0x2+1,

    R_RtuReg_LineEle = 0x610,//20
    R_RtuReg_LineEleSize = 0x5+1,//取两个

    R_RtuReg_OutputSw = 0x700,//21
    R_RtuReg_OutputSwSize = 0x17+1,//

    R_RtuReg_OutputNum = 0x800,//22
    R_RtuReg_OutputNumSize = 0x1,

//    R_RtuReg_LinkFlag = 0x810,//23
//    R_RtuReg_LinkFlagSize = 0x1,

    R_RtuReg_DevType= 0x820,//23  1-4 单相的A-D系列 5-8 三相的A-D系列
    R_RtuReg_DevTypeSize = 0x1,

    R_RtuReg_SlaveNum = 0x830,//24
    R_RtuReg_SlaveNumSize = 0x1,

    R_RtuReg_DevIP = 0x900,//25
    R_RtuReg_DevIPSize =0x2,

    R_RtuReg_CmdNum = 25,
};

#endif // R_SETCMDENUM_H
