#include "rtutrans.h"

RtuTrans::RtuTrans(QObject *parent)
{

}

bool RtuTrans::setValue(sRtuSetCmd &cmd)
{
    return sentSetCmd(cmd.addr, cmd.reg, cmd.value, 5);
}
