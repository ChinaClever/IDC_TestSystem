﻿#include "zset_snmpthread.h"

ZSet_SnmpThread::ZSet_SnmpThread(QObject *parent) : QThread(parent)
{
    mMutex = new QMutex();

    isRun = false;
    mSnmp = Z_SnmpTrans::bulid();
}

ZSet_SnmpThread::~ZSet_SnmpThread()
{
    isRun = false;
    wait();
}

void ZSet_SnmpThread::setCmd(const sSnmpSetCmd &cmd)
{
    mList.append(cmd);

    //     mSnmp->setValue(cmd);
}


/**
 * @brief 发送设置命令
 * @param addr 地址
 * @param reg 寄存吕
 * @param value 值
 * @return true
 */
int ZSet_SnmpThread::sentSetCmd(const sSnmpSetCmd &cmd)
{
    return mSnmp->setValue(cmd);
}

void ZSet_SnmpThread::run()
{
    if(isRun == false) {
        isRun = true;

        for(int i=0; i<mList.size(); ++i)
        {
            QString str = tr("命令 %1 执行").arg(i+1);
            int ret = sentSetCmd(mList.at(i));
            if(ret) {
                str += tr("成功!!");
            } else {
                str += tr("失败!!");
            }

            msleep(100);
            emit cmdSig(str);
        }

        mList.clear();
        isRun = false;
    }
}
