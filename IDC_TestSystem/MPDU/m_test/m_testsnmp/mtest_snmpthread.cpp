#include "mtest_snmpthread.h"

MTest_SnmpThread::MTest_SnmpThread(QObject *parent) : QThread(parent)
{
    mMutex = new QMutex();

    isRun = false;
    mSnmp = M_SnmpTrans::bulid();
}

MTest_SnmpThread::~MTest_SnmpThread()
{
    isRun = false;
    wait();
}


/**
 * @brief 发送设置命令
 * @param addr 地址
 * @param reg 寄存吕
 * @param value 值
 * @return true
 */
int MTest_SnmpThread::sentSetCmd(const sSnmpSetCmd &cmd)
{
    return mSnmp->setValue(cmd);
}

void MTest_SnmpThread::run()
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

            emit cmdSig(str);
        }

        mList.clear();
        isRun = false;
    }
}
