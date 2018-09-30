/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ztest_mainwid.h"
#include "z_com/z_datapackets.h"
#include "ztest_config.h"
#include "ztest_corethread.h"

ZTest_MainWid::ZTest_MainWid(QWidget *parent) : TestMainWid(parent)
{
    mConfig = ZTest_Config::bulid();
    mTrans = new ZTest_TransThread(this);
    mCoreThread = new ZTest_CoreThread(this);
    mPackets  = Z_DataPackets::bulid()->packets;
}
