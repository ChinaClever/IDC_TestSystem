/*
 * Si 设备数量
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "sisetdevnumdlg.h"
#include "ui_sisetdevnumdlg.h"
#include "si_com/siconfigfile.h"

SiSetDevNumDlg::SiSetDevNumDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SiSetDevNumDlg)
{
    ui->setupUi(this);
    initWid();
    groupBox_background_icon(this);
}

SiSetDevNumDlg::~SiSetDevNumDlg()
{
    delete ui;
}

void SiSetDevNumDlg::initWid()
{
    SiConfigFile *config = SiConfigFile::bulid();
    int num = config->item->devNum;
    ui->spinBox->setValue(num);
}

int SiSetDevNumDlg::getNum()
{
    return ui->spinBox->value();
}

void SiSetDevNumDlg::on_cancelBtn_clicked()
{
    this->close();
}

void SiSetDevNumDlg::on_okBtn_clicked()
{
    this->accept();
}
