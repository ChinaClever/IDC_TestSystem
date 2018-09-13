/*
 * 地址设置
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_addrsetwid.h"
#include "ui_si_addrsetwid.h"


SI_AddrSetWid::SI_AddrSetWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SI_AddrSetWid)
{
    ui->setupUi(this);

    QTimer::singleShot(500,this,SLOT(initFunSLot()));
}

SI_AddrSetWid::~SI_AddrSetWid()
{
    delete ui;
}

/**
 * @brief 初始化
 */
void SI_AddrSetWid::initFunSLot()
{
    sConfigItem *item = SiConfigFile::bulid()->item;
    ui->comboBox->setCurrentIndex(item->lineNum-1);
}

/**
 * @brief 更新数据
 * @param pkt
 */
void SI_AddrSetWid::updateData(SI_Rtu_Recv *pkt)
{
    bool en = true;
    int addr = ui->addrSpinBox->value();
    int line = ui->comboBox->currentIndex() + 1;

    int ret = SI_RtuThread::bulid()->transData(addr, line, pkt, 25);
    if(ret > 0) {
        emit updateSig(addr);
        InfoMsgBox box(this, tr("与设备连接成功，数据已刷新!!"));
    } else {
        CriticalMsgBox box(this, tr("与设备连接失败"));
        en = false;
    }

    ui->editBtn->setEnabled(en);
    ui->editSpinBox->setEnabled(en);
}

/**
 * @brief 刷新
 */
void SI_AddrSetWid::on_sureBtn_clicked()
{
    updateData(m_pkt);
}

/**
 * @brief 编辑窗口
 */
void SI_AddrSetWid::on_editBtn_clicked()
{
    int addr = ui->addrSpinBox->value();
    int value = ui->editSpinBox->value();

    bool ret =SI_RtuThread::bulid()->sentSetCmd(addr,SI_Addr_CMD, value, 20);
    if(ret) {
        ui->addrSpinBox->setValue(value);
        InfoMsgBox box(this, tr("地址修改成功，数据已刷新！！"));
        on_sureBtn_clicked();
    } else {
        CriticalMsgBox box(this, tr("地址修改失败！！！"));
    }
}
