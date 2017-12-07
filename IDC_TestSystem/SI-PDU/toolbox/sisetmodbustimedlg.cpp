/*
 * Si 传输间隔时间
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "sisetmodbustimedlg.h"
#include "ui_sisetmodbustimedlg.h"
#include "si_com/siconfigfile.h"


SiSetModbusTimeDlg::SiSetModbusTimeDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SiSetModbusTimeDlg)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
}

SiSetModbusTimeDlg::~SiSetModbusTimeDlg()
{
    delete ui;
}


void SiSetModbusTimeDlg::initWid()
{
    SiConfigFile *config = SiConfigFile::bulid();
    int num = config->item->cmdModel;
    ui->comboBox->setCurrentIndex(num);
}


int SiSetModbusTimeDlg::getIndex()
{
    return  ui->comboBox->currentIndex();
}

void SiSetModbusTimeDlg::on_okBtn_clicked()
{
    this->accept();
}

void SiSetModbusTimeDlg::on_cancelBtn_clicked()
{
    this->close();
}
