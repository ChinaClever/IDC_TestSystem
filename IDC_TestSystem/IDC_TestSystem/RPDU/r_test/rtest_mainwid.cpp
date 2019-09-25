/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "rtest_mainwid.h"
#include "r_com/r_datapackets.h"
#include "rtest_config.h"
#include "rtest_corethread.h"

RTest_MainWid::RTest_MainWid(QWidget *parent) : TestMainWid(parent)
{
    mConfig = RTest_Config::bulid();
    mTrans = new RTest_TransThread(this);
    mCoreThread = new RTest_CoreThread(this);
    mPackets  = R_DataPackets::bulid()->packets;
}
