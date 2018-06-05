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
    void tgBox(sBoxData *box);
    void tgObj(sBoxData *box);
    void startBox();

    void lineTgObj(sBoxData *box, int line, int loop);
    void LineTg(sBoxData *box);

    void bulidPf(BUS_sObjUnit *unit);
    int averData(int *data, int len);

};

#endif // BUS_DPTG_H
