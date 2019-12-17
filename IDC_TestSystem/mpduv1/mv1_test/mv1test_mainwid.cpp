#include "mv1test_mainwid.h"
#include "mv1_com/mv1_datapackets.h"
#include "mv1test_config.h"
#include "mv1test_corethread.h"

MV1Test_MainWid::MV1Test_MainWid(QWidget *parent) : TestMainWid(parent)
{
    mConfig = MV1Test_Config::bulid();
    mTrans = new MV1Test_TransThread(this);
    mCoreThread = new MV1Test_CoreThread(this);
    mPackets  = MV1_DataPackets::bulid()->packets;
}
