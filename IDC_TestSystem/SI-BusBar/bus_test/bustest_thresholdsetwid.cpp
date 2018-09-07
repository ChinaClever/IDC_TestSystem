#include "bustest_thresholdsetwid.h"
#include "ui_bustest_thresholdsetwid.h"
#include "bus_com/buspacketsi.h"
#include "bus_rtu/bus_rturecv.h"
#include "bus_rtu/bus_rtutrans.h"
#include <QGridLayout>

BUSTEST_ThresholdSetWid::BUSTEST_ThresholdSetWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BUSTEST_ThresholdSetWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->addWidget(this);

    QTimer::singleShot(2500,this,SLOT(on_updateBtn_clicked())); //延时初始化
}

BUSTEST_ThresholdSetWid::~BUSTEST_ThresholdSetWid()
{
    delete ui;
}
void BUSTEST_ThresholdSetWid::initWidget()
{
    int bus = ui->busBox->currentIndex();
    int addr = ui->addrBox->currentIndex() +1;

    int id = ui->lineBox->currentIndex();
    sObjData* obj =&( BusPacketSi::bulid()->getBox(bus , addr)->data.loop[id]);

    ui->volMinBox->setValue(obj->vol.min);
    ui->volMaxBox->setValue(obj->vol.max);

    ui->curMinBox->setValue(obj->cur.min);
    ui->curMaxBox->setValue(obj->cur.max);
}

void BUSTEST_ThresholdSetWid::sendCmd()
{
    sRtuSentCom cmd;
    mAddr = cmd.addr = ui->addrBox->currentIndex() + 1;
    if(ui->checkBox->isChecked()) cmd.addr = 0xff;

    int id = ui->lineBox->currentIndex();
    cmd.reg = 0x1002 + id *2;
    cmd.len = ui->volMaxBox->value();
    bool ret1 = BUS_RtuTrans::bulid()->sentCmd(cmd);

    cmd.reg += 1;
    cmd.len = ui->volMinBox->value();
    bool ret2 = BUS_RtuTrans::bulid()->sentCmd(cmd);

    cmd.reg = 0x1020 + id *2;
    cmd.len = ui->curMaxBox->value();
    bool ret3 = BUS_RtuTrans::bulid()->sentCmd(cmd);

    cmd.reg += 1;
    cmd.len = ui->curMinBox->value();
    bool ret4 = BUS_RtuTrans::bulid()->sentCmd(cmd);

    if(ret1 && ret2 && ret3 && ret4) {
        InfoMsgBox box(this, tr("阈值修改成功，数据已刷新！！"));
    } else {
        CriticalMsgBox box(this, tr("阈值修改失败！！！"));
    }
}


void BUSTEST_ThresholdSetWid::on_updateBtn_clicked()
{
    initWidget();
}

void BUSTEST_ThresholdSetWid::on_setBtn_clicked()
{
    QuMsgBox box(this, tr("确定要修改阈值？？"));
    if(box.Exec())    {
        sendCmd();
        QTimer::singleShot(12500,this,SLOT(on_updateBtn_clicked())); //延时初始化
        InfoMsgBox msg(this, tr("需要十秒数据才能重新刷新!!"));
    }
}

void BUSTEST_ThresholdSetWid::on_busBox_currentIndexChanged(int index)
{
    initWidget();
    emit updateBus(index);
}

void BUSTEST_ThresholdSetWid::on_addrBox_currentIndexChanged(int index)
{
    initWidget();
    emit updateAddr(index);
}

void BUSTEST_ThresholdSetWid::on_lineBox_currentIndexChanged(int index)
{
    initWidget();
}
