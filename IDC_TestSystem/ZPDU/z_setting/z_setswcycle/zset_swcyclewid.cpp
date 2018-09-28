#include "zset_swcyclewid.h"
#include "ui_zset_swcyclewid.h"

ZSet_SwCycleWid::ZSet_SwCycleWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZSet_SwCycleWid)
{
    ui->setupUi(this);
    mReg = Z_RtuReg_OutputSw;
    initwid();
}

ZSet_SwCycleWid::~ZSet_SwCycleWid()
{
    delete ui;
}
void ZSet_SwCycleWid::initwid()
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3, ui->widget_4, ui->widget_5,ui->widget_6,
                      ui->widget_7, ui->widget_8, ui->widget_9, ui->widget_10, ui->widget_11, ui->widget_12,
                      ui->widget_13,ui->widget_14, ui->widget_15, ui->widget_16,ui->widget_17,ui->widget_18,
                      ui->widget_19,ui->widget_20,ui->widget_21,ui->widget_22,ui->widget_23,ui->widget_24};

    for(int i=0; i<24; ++i) {
        mWid[i] = new ZSet_SwCycleItemWid(wid[i]);
        mWid[i]->init(i);
    }

    timer =new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));

    caseCount = 0;
    cycleCount = 0;

    mSnmp = new ZSet_SnmpThread(this);
    connect(mSnmp, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));

    mRtu = new ZSet_RtuThread(this);
    mRtu->mReg = mReg;
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}
void ZSet_SwCycleWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void ZSet_SwCycleWid::on_checkBox_clicked(bool checked)
{
    for(int i=0; i<24; ++i) {
        mWid[i]->setSelect(checked);
    }
}

void ZSet_SwCycleWid::on_radioButton_clicked(bool checked)
{
    if(checked)
    {
        ui->cycleCountpinBox->setEnabled(false);
        ui->label_3->setEnabled(false);
    }
    else
    {
        ui->cycleCountpinBox->setEnabled(true);
        ui->label_3->setEnabled(true);
    }
    caseCount = 0;
    cycleCount = 0;
    QString str = QString(tr("当前次数：%1次")).arg(cycleCount);
    ui->cycleCountlab->setText(str);
}
QString ZSet_SwCycleWid::getOid(int i)
{
    QString oid = QString("%1.%2.%3.7.%4.0")
            .arg(MIB_OID_CLEVER)
            .arg(Z_MIB_OID)
            .arg(ui->spinBox->value())
            .arg(i+1);
    return oid;
}
void ZSet_SwCycleWid::snmpFirstCase(int& mtimers)
{
    for(int i = mtimers ; i < select.size() ; ++i)
     {
        sSnmpSetCmd cmd;

        cmd.oid = getOid(select[i]);
        cmd.type = SNMP_STRING_TYPE;
        cmd.value.append(i == 0?"ON":"OFF");
        mSnmp->setCmd(cmd);
    }  
}

void ZSet_SwCycleWid::snmpOtherCase(QList<int> & select , int& mtimers ,bool end)
{
    sSnmpSetCmd cmd;

    cmd.oid = getOid(select[mtimers-1]);
    cmd.type = SNMP_STRING_TYPE;
    cmd.value.append("OFF");
    mSnmp->setCmd(cmd);
    if(end)
    {
        sSnmpSetCmd cmd1;
        cmd1.oid = getOid(select[mtimers]);
        cmd1.type = SNMP_STRING_TYPE;
        cmd1.value.append("ON");
        mSnmp->setCmd(cmd1);
    }
}
void ZSet_SwCycleWid::sendSnmp(QList<int>& select , int& mtimers)
{
    if(mtimers == select.size())
    {
        snmpOtherCase(select , mtimers , false);
        caseCount = 0;

        mSnmp->start();

        ui->textEdit->clear();
        cycleCount++;
        QString str = QString(tr("当前次数：%1次")).arg(cycleCount);
        ui->cycleCountlab->setText(str);
        bool flag = ui->radioButton->isChecked();
        if(!flag)
        {
            if(ui->cycleCountpinBox->value() == cycleCount)
             {
                timer->stop();
                cycleCount = 0;
            }
        }
        return;
    }
    (mtimers == 0)? snmpFirstCase(mtimers): snmpOtherCase(select , mtimers , true);
    caseCount++;
    mSnmp->start();

    ui->textEdit->clear();
}
void ZSet_SwCycleWid::rtuFirstCase(int& mtimers)
{

    sRtuSetCmd cmd;
    cmd.addr = ui->spinBox->value();
    cmd.reg = mReg + mtimers;
    cmd.value = 1;
    mRtu->setCmd(cmd);
}
void ZSet_SwCycleWid::rtuOtherCase(QList<int> & select , int& mtimers ,bool end)
{
    sRtuSetCmd cmd;
    cmd.addr = ui->spinBox->value();
    cmd.reg = mReg + select[mtimers - 1];
    cmd.value = 0;
    mRtu->setCmd(cmd);
    if(end)
    {
        sRtuSetCmd cmd1;
        cmd1.addr = ui->spinBox->value();
        cmd1.reg = mReg + select[mtimers];
        cmd1.value = 1;
        mRtu->setCmd(cmd1);
    }
}
void ZSet_SwCycleWid::sendRtu(QList<int>& select , int& mtimers)
{
    if(mtimers == select.size())
    {
        rtuOtherCase(select , mtimers , false);
        caseCount = 0;

        mRtu->start();

        ui->textEdit->clear();
        cycleCount++;
        QString str = QString(tr("当前次数：%1次")).arg(cycleCount);
        ui->cycleCountlab->setText(str);
        bool flag = ui->radioButton->isChecked();
        if(!flag)
        {
            if(ui->cycleCountpinBox->value() == cycleCount)
             {
                timer->stop();
                cycleCount = 0;
            }
        }
        return;
    }
    (mtimers == 0)? rtuFirstCase(mtimers): rtuOtherCase(select , mtimers , true);
    caseCount++;
    mRtu->start();

    ui->textEdit->clear();
}
void ZSet_SwCycleWid::produceCmd(QList<int> & select , int& mtimers)
{
    sConfigItem *item = Z_ConfigFile::bulid()->item;
    if(item->setMode == Test_SNMP)
    {
        sendSnmp(select , mtimers);
    }
    else
    {
        sendRtu(select , mtimers);
    }
}
void ZSet_SwCycleWid::update()
{
    produceCmd(select , caseCount);
}
void ZSet_SwCycleWid::on_startBtn_clicked()
{
    select.clear();
    for(int i=0; i<24; ++i) {
        if(mWid[i]->select()) {
            select.append(i);
        }
    }

    timer->start(ui->timespinBox->value()*1000);

}

void ZSet_SwCycleWid::on_stopBtn_clicked()
{
    timer->stop();

    caseCount = 0;
    cycleCount = 0;
    QString str = QString(tr("当前次数：%1次")).arg(cycleCount);
    ui->cycleCountlab->setText(str);
}
