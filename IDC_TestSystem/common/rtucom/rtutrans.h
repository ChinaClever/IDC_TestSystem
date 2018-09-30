#ifndef RTUTRANS_H
#define RTUTRANS_H
#include "rtusentcom.h"

class RtuTrans : public QThread
{
public:
    RtuTrans(QObject *parent = nullptr);

     bool setValue(const sRtuSetCmd &cmd);
     virtual bool sentSetCmd(int addr, int reg, ushort value, int msecs) = 0;
};

#endif // RTUTRANS_H
