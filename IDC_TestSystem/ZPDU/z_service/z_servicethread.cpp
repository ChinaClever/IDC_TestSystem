#include "z_servicethread.h"
#include "z_com/z_datapackets.h"

Z_ServiceThread::Z_ServiceThread(QObject *parent) : WebServiceThread(parent)
{
    mBuildJson = Z_BuildJson::bulid();
    mPackets = Z_DataPackets::bulid()->packets;
}
