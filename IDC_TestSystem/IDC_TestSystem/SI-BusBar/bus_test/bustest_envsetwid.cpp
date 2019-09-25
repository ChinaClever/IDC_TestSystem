#include "bustest_envsetwid.h"
#include "ui_bustest_envsetwid.h"
#include "bus_com/buspacketsi.h"
#include "bus_rtu/bus_rturecv.h"
#include "bus_rtu/bus_rtutrans.h"
#include <QGridLayout>
BUSTEST_EnvSetWid::BUSTEST_EnvSetWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BUSTEST_EnvSetWid)
{
    ui->setupUi(this);

    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);

    mAddr = 1;
    mBus = 1;
    QTimer::singleShot(2500,this,SLOT(on_updateBtn_clicked())); //延时初始化
}

BUSTEST_EnvSetWid::~BUSTEST_EnvSetWid()
{
    delete ui;
}
void BUSTEST_EnvSetWid::updateAddr(int Addr)
{
    mAddr = Addr + 1;
    initWidget();
}
void BUSTEST_EnvSetWid::updateBus(int Bus)
{
    mBus = Bus;
    initWidget();
}

void BUSTEST_EnvSetWid::initWidget()
{
    int envid = ui->envBox->currentIndex();
    on_changeEnvBtn_clicked();

    sDataUnit* obj = &(BusPacketSi::bulid()->getBox(mBus , mAddr)->data.env.tem[envid]);
    ui->tempMinBox->setValue(obj->min);
    ui->tempMaxBox->setValue(obj->max);
}
void BUSTEST_EnvSetWid::sendCmd()
{    
    BUS_Rtu_Sent cmd;
    cmd.addr = mAddr;

    if(ui->changeEnvBtn->isChecked())
    {
        if(ui->checkBox->isChecked()) cmd.addr = 0xff;
        int envid = ui->envBox->currentIndex();
        cmd.reg = 0x1032 + envid *2;
        cmd.len = ui->tempMaxBox->value();
        bool ret1 = BUS_RtuTrans::bulid()->sentCmd(cmd);

        cmd.reg += 1;
        cmd.len = ui->tempMinBox->value();
        bool ret2 =BUS_RtuTrans::bulid()->sentCmd(cmd);

        if(ret1 && ret2) {
            InfoMsgBox box(this, tr("阈值修改成功，数据已刷新！！"));
        } else {
            CriticalMsgBox box(this, tr("阈值修改失败！！！"));
        }
    }

    if(ui->changeAddrBtn->isChecked())
    {
        cmd.reg = 0x1001;
        cmd.len = ui->addrBox->currentIndex()+1;
        bool ret1 =BUS_RtuTrans::bulid()->sentCmd(cmd);
        if(ret1 ) {
            InfoMsgBox box(this, tr("地址修改成功，数据已刷新！！"));
        } else {
            CriticalMsgBox box(this, tr("地址修改失败！！！"));
        }
    }

    if(ui->changeBaudBtn->isChecked())
    {
        cmd.reg = 0x1038;
        cmd.len = ui->baudBox->currentIndex()+1;

        bool ret1 =BUS_RtuTrans::bulid()->sentCmd(cmd);
        if(ret1 ) {
            InfoMsgBox box(this, tr("波特率修改成功，数据已刷新！！"));
        } else {
            CriticalMsgBox box(this, tr("波特率修改失败！！！"));
        }
    }
}

void BUSTEST_EnvSetWid::on_updateBtn_clicked()
{
    initWidget();
}

void BUSTEST_EnvSetWid::on_setBtn_clicked()
{

    QuMsgBox box(this, tr("确定要修改阈值？？"));
    if(box.Exec())    {
        sendCmd();
        QTimer::singleShot(12500,this,SLOT(on_updateBtn_clicked())); //延时初始化
        InfoMsgBox msg(this, tr("需要十秒数据才能重新刷新!!"));
    }
}
ushort BUSTEST_EnvSetWid::change(int index)
{
    ushort baud = 0x0000;
    switch(index)
    {
    case 0:
        baud=0x0001;break;
    case 1:
        baud=0x0002;break;
    case 2:
        baud=0x0003;break;
    case 3:
        baud=0x0004;break;
    default:break;
    }
    return baud;
}

void BUSTEST_EnvSetWid::on_changeEnvBtn_clicked()
{
    if(ui->changeEnvBtn)
    {
        ui->label->setEnabled(false);
        ui->addrBox->setEnabled(false);

        ui->label_6->setEnabled(false);
        ui->baudBox->setEnabled(false);

        ui->label_2->setEnabled(true);
        ui->envBox->setEnabled(true);
        ui->tempMinBox->setEnabled(true);
        ui->label_3->setEnabled(true);
        ui->tempMaxBox->setEnabled(true);
        ui->label_4->setEnabled(true);
        ui->label_5->setEnabled(true);

    }
}

void BUSTEST_EnvSetWid::on_changeAddrBtn_clicked()
{
    if(ui->changeAddrBtn)
    {
        ui->label_2->setEnabled(false);
        ui->envBox->setEnabled(false);
        ui->tempMinBox->setEnabled(false);
        ui->label_3->setEnabled(false);
        ui->tempMaxBox->setEnabled(false);
        ui->label_4->setEnabled(false);
        ui->label_5->setEnabled(false);

        ui->label_6->setEnabled(false);
        ui->baudBox->setEnabled(false);

        ui->label->setEnabled(true);
        ui->addrBox->setEnabled(true);
    }
}

void BUSTEST_EnvSetWid::on_changeBaudBtn_clicked()
{
    ui->label->setEnabled(false);
    ui->addrBox->setEnabled(false);

    ui->label_2->setEnabled(false);
    ui->envBox->setEnabled(false);
    ui->tempMinBox->setEnabled(false);
    ui->label_3->setEnabled(false);
    ui->tempMaxBox->setEnabled(false);
    ui->label_4->setEnabled(false);
    ui->label_5->setEnabled(false);

    ui->label_6->setEnabled(true);
    ui->baudBox->setEnabled(true);

}

void BUSTEST_EnvSetWid::on_envBox_currentIndexChanged(int index)
{
    initWidget();
}
