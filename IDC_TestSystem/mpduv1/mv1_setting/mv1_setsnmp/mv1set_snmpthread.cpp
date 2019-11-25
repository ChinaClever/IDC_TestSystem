#include "mv1set_snmpthread.h"

MV1Set_SnmpThread::MV1Set_SnmpThread(QObject *parent) : QThread(parent)
{
    mMutex = new QMutex();

    isRun = false;
    mSnmp = MV1_SnmpTrans::bulid();
}

MV1Set_SnmpThread::~MV1Set_SnmpThread()
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
int MV1Set_SnmpThread::sentSetCmd(const sSnmpSetCmd &cmd)
{
    return mSnmp->setValue(cmd);
}

void MV1Set_SnmpThread::run()
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
