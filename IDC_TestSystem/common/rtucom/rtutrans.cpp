#include "rtutrans.h"

RtuTrans::RtuTrans(QObject *parent)
{

}

bool RtuTrans::setValue(const sRtuSetCmd &cmd)
{
    return sentSetCmd(cmd.addr, cmd.reg, cmd.value, 5);
}
