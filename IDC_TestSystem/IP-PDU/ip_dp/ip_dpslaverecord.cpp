#include "ip_dpslaverecord.h"
#include "ip_sql/ipdbrealrecords.h"

IP_DpSlaveRecord::IP_DpSlaveRecord(QObject *parent) : QThread(parent)
{
    isRun  = false;
}

IP_DpSlaveRecord::~IP_DpSlaveRecord()
{
    isRun = false;
    wait();
}

void IP_DpSlaveRecord::saveLogs()
{
    int num = IpDataPackets::bulid()->devNum;
    for(int i=1; i<=num; ++i) {
        saveLogItem(i);
    }
}

void IP_DpSlaveRecord::saveLogItem(int id)
{
    IpDevPacket *dev = IpDataPackets::bulid()->getDev(id);
    IP_Rtu_Recv *packet = &(dev->rtuData);
    if(packet->offLine > 0)
    {
        int line = packet->data.lineNum;
        for(int i=0; i<line; ++i)
        {
            IpDbRealRecordItem item;

            item.dev_id = id;
            item.line = i+1;
            item.sw = packet->data.sw[i];
            if(item.sw) {
                item.sw_str = tr("断开");
            } else  {
                item.sw_str = tr("闭合");
            }

            item.vol = packet->data.vol.value[i] / COM_RATE_VOL;
            item.cur = packet->data.cur.value[i] / COM_RATE_CUR;
            item.pow = packet->data.pow[i] / COM_RATE_POW;
            item.apow = packet->data.activePow[i] / COM_RATE_POW;
            item.pf = packet->data.pf[i] / COM_RATE_PF;
            item.ele = packet->data.ele[i] / COM_RATE_ELE;

            IpDbRealRecords::bulid()->insertItem(item);
            msleep(LOG_DELAY);
        }
    }
}



void IP_DpSlaveRecord::run()
{
    if(isRun == false)
    {
        isRun  = true;

        saveLogs();

        isRun  = false;
    }
}
