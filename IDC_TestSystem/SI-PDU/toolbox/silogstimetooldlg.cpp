/*
 * Si 日志保存时间间隔对话框
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "silogstimetooldlg.h"
#include "ui_silogstimetooldlg.h"
#include "si_com/siconfigfile.h"

SiLogsTimeToolDlg::SiLogsTimeToolDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SiLogsTimeToolDlg)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    initWid();
}

SiLogsTimeToolDlg::~SiLogsTimeToolDlg()
{
    delete ui;
}

/**
 * @brief 初始化窗口
 */
void SiLogsTimeToolDlg::initWid()
{
    SiConfigFile *config = SiConfigFile::bulid();
    int num = config->item->logMins;
    ui->spinBox->setValue(num);
}

int SiLogsTimeToolDlg::getTime()
{
    return ui->spinBox->value();
}


void SiLogsTimeToolDlg::on_okBtn_clicked()
{
    this->accept();
}

void SiLogsTimeToolDlg::on_cancelBtn_clicked()
{
    this->close();
}
