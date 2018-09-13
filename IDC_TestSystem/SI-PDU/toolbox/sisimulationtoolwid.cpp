/*
 * Si 模拟窗口
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "sisimulationtoolwid.h"
#include "ui_sisimulationtoolwid.h"
#include "si_com/siconfigfile.h"
#include <QGridLayout>
#include "msgbox.h"

SiSimulationToolWid::SiSimulationToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SiSimulationToolWid)
{
    ui->setupUi(this);

    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
    //    com_setBackColour("",this);
}

SiSimulationToolWid::~SiSimulationToolWid()
{
    delete ui;
}

/**
 * @brief 开始模拟测试
 */
void SiSimulationToolWid::startSimulateTest()
{
    SiConfigFile *config = SiConfigFile::bulid();
    config->item->testMode = Test_Rtu;
    emit simulateSig(Test_Rtu);

    ui->mnTestBtn->setText(tr("停止测试"));
}

/**
 * @brief 停止模拟测试
 */
bool SiSimulationToolWid::stopSimulateTest()
{
    bool ret = false;
    QuMsgBox box(this, tr("是否停止测试？？"));
    if(box.Exec()) {
        SiConfigFile *config = SiConfigFile::bulid();
        config->item->testMode = Test_Stop;
        emit simulateSig(Test_Stop);

        ret = true;
        ui->mnTestBtn->setText(tr("一键模拟"));
    }

    return ret;
}

void SiSimulationToolWid::on_mnTestBtn_clicked()
{
    SiConfigFile *config = SiConfigFile::bulid();
    int mode = config->item->testMode;

    switch (mode) {
    case Test_Stop:
        startSimulateTest();
        break;

    case Test_Rtu:
        stopSimulateTest();
        break;

    default:
        CriticalMsgBox box(this, tr("请停止其它操作!!"));
        break;
    }

}

void SiSimulationToolWid::on_envBtn_clicked()
{
    emit simulateSig(Info_Env);
}

void SiSimulationToolWid::on_thresholdBtn_clicked()
{
    emit simulateSig(Info_LineThreshold);
}

void SiSimulationToolWid::on_transBtn_clicked()
{
    emit simulateSig(Info_Trans);
}

void SiSimulationToolWid::on_realBtn_clicked()
{
    emit simulateSig(Info_Line);
}

void SiSimulationToolWid::on_settingBtn_clicked()
{
    SiConfigFile *config = SiConfigFile::bulid();
    int mode = config->item->testMode;

    if(mode != Test_Stop) {
        bool ret = stopSimulateTest();
        if(!ret) return;
    }

    emit simulateSig(Info_Set);
}
