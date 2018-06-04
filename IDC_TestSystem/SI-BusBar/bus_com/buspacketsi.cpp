#include "buspacketsi.h"

BusPacketSi::BusPacketSi()
{
    memset(&mBus, 0, sizeof(sBusData)*BUS_NUM);
}

BusPacketSi *BusPacketSi::bulid()
{
    static BusPacketSi* sington = nullptr;
    if(sington == nullptr)
        sington = new BusPacketSi();
    return sington;
}
