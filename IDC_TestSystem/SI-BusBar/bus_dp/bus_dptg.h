#ifndef BUS_DPTG_H
#define BUS_DPTG_H
#include "bus_com/buspacketsi.h"

class BUS_DpTg
{
public:
    BUS_DpTg();

    void tg();

protected:
    void tgBus(sBusData *bus);
    void tgBox(sDataPacket *box);
    void tgObj(sDevData *box);
    void startBox();

    void lineTgObj(sDevData *box, int line, int loop);
    void LineTg(sDataPacket *box);

    void bulidPf(sObjData *unit);
    int averData(int *data, int len);

};

#endif // BUS_DPTG_H
