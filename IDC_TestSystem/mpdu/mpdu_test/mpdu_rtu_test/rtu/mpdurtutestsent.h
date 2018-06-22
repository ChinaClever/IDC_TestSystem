#ifndef MPDURTUTESTSENT_H
#define MPDURTUTESTSENT_H
#include "serialportdlg.h"

struct MPDU_RtuTest_Sent : public Rtu_Sent_Com{
    MPDU_RtuTest_Sent(){len=0;} // 下位机有问题
};


class MpduRtuTestSent
{
public:
    MpduRtuTestSent();
    int sentDataBuff(uchar addr, uchar len, uchar *buf);
    int sentCmdBuff(uchar addr, ushort reg, ushort value, uchar *buf);
};

#endif // MPDURTUTESTSENT_H
