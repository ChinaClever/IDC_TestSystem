#include "settingtoolwid.h"
#include "ui_settingtoolwid.h"
#include "QGridLayout"
SettingToolWid::SettingToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingToolWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);
    ippdu();
    QTimer::singleShot(500,this,SLOT(initFunSLot())); //延时初始化
}

SettingToolWid::~SettingToolWid()
{
    delete ui;
}

void SettingToolWid::initFunSLot()
{
    initLineNum();
    initModbusTime();
    initDevCmd();
    initDevNum();
    initOutputNum();
    initVersion();
}

void SettingToolWid::ippdu(bool hide)
{
    ui->vBox->setHidden(hide);
    ui->vBtn->setHidden(hide);
    ui->vLabel->setHidden(hide);
}

/**
 * @brief 更新
 * @param num
 */
void SettingToolWid::updateDevCmd(int num)
{
    mConfig->item->cmdModel = num;
    mConfig->setModbusCmd(num);
}

void SettingToolWid::initDevCmd()
{
    int num = mConfig->getModbusCmd();
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
    mConfig->item->msecs = 5*(num+1);
    mConfig->setModbusTime(num);
}

void SettingToolWid::initModbusTime()
{
    int num = mConfig->getModbusTime();
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
    mConfig->item->devNum = num;
    mConfig->setDevNum(num);
}

void SettingToolWid::initDevNum()
{
    int num = mConfig->getDevNum();;
    updateDevNum(num);
    ui->spinBox->setValue(num);
}

void SettingToolWid::on_devNumBtn_clicked()
{
    updateDevNum(ui->spinBox->value());
}

void SettingToolWid::updateOutputNum(int num)
{
    mConfig->item->outputNum = num;
    mConfig->setOutputNum(num);
}

void SettingToolWid::initOutputNum()
{
    int num = mConfig->getOutputNum();;
    updateOutputNum(num);
    ui->outputSpinBox->setValue(num);
}

void SettingToolWid::on_outputNumBtn_clicked()
{
    updateOutputNum(ui->outputSpinBox->value());
}

/**
 * @brief 更新相数
 * @param num
 */
void SettingToolWid::updateLineNum(int num)
{
    mConfig->item->lineNum = num;
    mConfig->setLineNum(num);
}

/**
 * @brief 初始化相数
 */
void SettingToolWid::initLineNum()
{
    int num = mConfig->getLineNum();
    updateLineNum(num);
    ui->lineSpinBox->setValue(num-1);
}

void SettingToolWid::on_lineBtn_clicked()
{
    updateOutputNum(ui->lineSpinBox->value()+1);
}


void SettingToolWid::updateVersion(int num)
{
    mConfig->item->v = num;
    mConfig->setVersion(num);
}

void SettingToolWid::initVersion()
{
    int num = mConfig->getVersion();;
    updateVersion(num);
    ui->vBox->setCurrentIndex(num);
}

void SettingToolWid::on_vBtn_clicked()
{
    updateVersion(ui->vBox->currentIndex());
}

