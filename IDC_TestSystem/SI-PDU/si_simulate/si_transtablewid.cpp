/*
 * Si 传输表格
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_transtablewid.h"

SI_TransTableWid::SI_TransTableWid(QWidget *parent) : TransTableWid(parent)
{
    mPackets = SIDataPackets::bulid()->packets;
}
