/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "dpsaverecord.h"

DpSaveRecord::DpSaveRecord(QObject *parent) : QThread(parent)
{
    mPackets = NULL;
    isRun  = false;
}

DpSaveRecord::~DpSaveRecord()
{
    isRun = false;
    wait();
}

void DpSaveRecord::saveLogs()
{
    int num = mPackets->devNum;
    for(int i=1; i<=num; ++i) {
        saveLogItem(i);
    }
}


void DpSaveRecord::run()
{
    if(isRun == false)
    {
        isRun  = true;

        if(mPackets)
            saveLogs();

        isRun  = false;
    }
}
