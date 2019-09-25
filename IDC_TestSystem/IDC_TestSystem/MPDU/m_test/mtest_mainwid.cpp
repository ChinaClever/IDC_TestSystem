#include "mtest_mainwid.h"
#include "m_com/m_datapackets.h"
#include "mtest_config.h"
#include "mtest_corethread.h"

MTest_MainWid::MTest_MainWid(QWidget *parent) : TestMainWid(parent)
{
    mConfig = MTest_Config::bulid();
    mTrans = new MTest_TransThread(this);
    mCoreThread = new MTest_CoreThread(this);
    mPackets  = M_DataPackets::bulid()->packets;
}
