/*
 * Si 设备相数
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "sisetlinenum.h"
#include "ui_sisetlinenum.h"
#include "si_com/siconfigfile.h"

SiSetLineNum::SiSetLineNum(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SiSetLineNum)
{
    ui->setupUi(this);
    initWid();
    groupBox_background_icon(this);
}

SiSetLineNum::~SiSetLineNum()
{
    delete ui;
}

void SiSetLineNum::initWid()
{
    SiConfigFile *config = SiConfigFile::bulid();
    int num = config->item->lineNum;

    switch (num) {
    case 1: ui->radioButton_1->setChecked(true);  break;
    case 2: ui->radioButton_2->setChecked(true);  break;
    case 3: ui->radioButton_3->setChecked(true);  break;
    default:
        break;
    }
}

int SiSetLineNum::getLineNum()
{
    int ret = 1;
    if(ui->radioButton_1->isChecked()) {
        ret = 1;
    } else if(ui->radioButton_2->isChecked()) {
        ret = 2;
    } else {
        ret = 3;
    }

    return ret;
}

void SiSetLineNum::on_cancelBtn_clicked()
{
    this->close();
}

void SiSetLineNum::on_okBtn_clicked()
{
    this->accept();
}
