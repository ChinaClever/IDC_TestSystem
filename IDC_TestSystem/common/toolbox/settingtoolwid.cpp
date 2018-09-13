#include "settingtoolwid.h"
#include "ui_settingtoolwid.h"

SettingToolWid::SettingToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingToolWid)
{
    ui->setupUi(this);

    QTimer::singleShot(500,this,SLOT(initFunSLot())); //延时初始化
}

SettingToolWid::~SettingToolWid()
{
    delete ui;
}

void SettingToolWid::initFunSLot()
{
    initModbusTime();
    initDevCmd();
    initDevNum();
    initOutputNum();
}

/**
 * @brief 更新
 * @param num
 */
void SettingToolWid::updateDevCmd(int num)
{
    config->item->cmdModel = num;
    config->setModbusCmd(num);
}

void SettingToolWid::initDevCmd()
{
    int num = config->getModbusCmd();
    updateDevCmd(num);

    ui->cmdBox->setCurrentIndex(num-1);
}

void SettingToolWid::on_cmdBtn_clicked()
{
    int num = ui->cmdBox->currentIndex();
    updateDevCmd(num+1);
}



/**
 * @brief 更新间隔时间
 * @param num
 */
void SettingToolWid::updateModbusTime(int num)
{
    config->item->msecs = 5*(num+1);
    config->setModbusTime(num);
}

void SettingToolWid::initModbusTime()
{
    int num = config->getModbusTime();
    updateModbusTime(num);
    ui->timeBox->setCurrentIndex(num);
}

void SettingToolWid::on_timeBtn_clicked()
{
    updateModbusTime(ui->timeBox->currentIndex());
}


/**
 * @brief 更新设备数量
 * @param num
 */
void SettingToolWid::updateDevNum(int num)
{
    config->item->devNum = num;
    config->setDevNum(num);
}

void SettingToolWid::initDevNum()
{
    int num = config->getDevNum();;
    updateDevNum(num);
    ui->spinBox->setValue(num);
}


void SettingToolWid::on_devNumBtn_clicked()
{
    updateDevNum(ui->spinBox->value());
}

void SettingToolWid::updateOutputNum(int num)
{
    config->item->outputNum = num;
    config->setOutputNum(num);
}

void SettingToolWid::initOutputNum()
{
    int num = config->getOutputNum();;
    updateOutputNum(num);
    ui->outputSpinBox->setValue(num);
}

void SettingToolWid::on_outputNumBtn_clicked()
{
    updateOutputNum(ui->outputSpinBox->value());
}
