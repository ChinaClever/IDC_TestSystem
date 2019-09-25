/*
 * 电能清除
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_elesetwid.h"
#include "ui_si_elesetwid.h"

SI_EleSetWid::SI_EleSetWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SI_EleSetWid)
{
    ui->setupUi(this);

    mAddr = 1;
}

SI_EleSetWid::~SI_EleSetWid()
{
    delete ui;
}

/**
 * @brief 更新数据
 * @param addr 设备地址
 * @param line 相数
 * @param array 数据
 * @param br 波特玄
 */
void SI_EleSetWid::updateData(int addr,int line, uint *array, int br)
{
    QString str = "---";
    ui->eleLabel_1->setText(str);
    ui->eleLabel_2->setText(str);
    ui->eleLabel_3->setText(str);

    double value = 0;
    switch (line) {
    case 3:
        value = array[2] / COM_RATE_ELE;
        str = QString::number(value) + "KWh";
        ui->eleLabel_3->setText(str);

    case 2:
        value = array[1] / COM_RATE_ELE;
        str = QString::number(value) + "KWh";
        ui->eleLabel_2->setText(str);

    case 1:
        value = array[0] / COM_RATE_ELE;
        str = QString::number(value) + "KWh";
        ui->eleLabel_1->setText(str);
        break;

    default:
        break;
    }
    mAddr = addr;

    if(br == 0) br = 1;
    else br--;
    ui->comboBox->setCurrentIndex(br);
}


/**
 * @brief 电能清除
 */
void SI_EleSetWid::on_cleverBtn_clicked()
{
    QuMsgBox box(this, tr("确定要清除电能？"));
    bool ret = box.Exec();
    if(ret) {
        int value = 0xffff;
        ret =SI_RtuTrans::bulid()->sentSetCmd(mAddr,SI_ELE_CMD, value, 20);
        if(ret) {
            updateData(mAddr, 0, NULL, 0);
            InfoMsgBox box(this, tr("修改成功！！， 请重新刷新数据"));
        } else {
            CriticalMsgBox box(this, tr("修改失败！！！"));
        }
    }
}

/**
 * @brief 波特率修改
 */
void SI_EleSetWid::on_editBtn_clicked()
{
    QuMsgBox box(this, tr("确定要修改波特率？"));
    bool ret = box.Exec();
    if(ret) {
        int value = ui->comboBox->currentIndex()+1;
        ret =SI_RtuTrans::bulid()->sentSetCmd(mAddr,SI_BR_CMD, value, 20);
        if(ret) {
            InfoMsgBox box(this, tr("修改成功！！， 请重新设置串口"));
        } else {
            CriticalMsgBox box(this, tr("修改失败！！！"));
        }
    }
}
