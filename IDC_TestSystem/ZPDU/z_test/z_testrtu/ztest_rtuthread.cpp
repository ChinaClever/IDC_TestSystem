#include "ztest_rtuthread.h"

ZTest_RtuThread::ZTest_RtuThread(QObject *parent) : QThread(parent)
{
    mReg = 0;
    mMutex = new QMutex();

    isRun = false;
    mRtu = Z_RtuTrans::bulid();
}

ZTest_RtuThread::~ZTest_RtuThread()
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
bool ZTest_RtuThread::sentSetCmd(int addr, int reg, ushort value, int msecs)
{
    return mRtu->sentSetCmd(addr,reg, value, msecs);
}

void ZTest_RtuThread::run()
{
    if(isRun == false) {
        isRun = true;

        for(int i=0; i<mList.size(); ++i)
        {
            int id = i+1;
            if(mReg) id = mList.at(i).reg - mReg+1;

            QString str = tr("输出位 %1 命令执行").arg(id);
            bool ret = sentSetCmd(mList.at(i).addr,mList.at(i).reg,mList.at(i).value, 5);
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


