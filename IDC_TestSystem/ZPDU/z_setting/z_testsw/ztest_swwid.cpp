#include "ztest_swwid.h"
#include "ui_ztest_swwid.h"

ZTest_SwWid::ZTest_SwWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZTest_SwWid)
{
    ui->setupUi(this);
    mReg = Z_RtuReg_OutputSw;
    initwid();
}

ZTest_SwWid::~ZTest_SwWid()
{
    delete ui;
}

void ZTest_SwWid::initwid()
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3, ui->widget_4, ui->widget_5,ui->widget_6,
                      ui->widget_7, ui->widget_8, ui->widget_9, ui->widget_10, ui->widget_11, ui->widget_12,
                      ui->widget_13,ui->widget_14, ui->widget_15, ui->widget_16,ui->widget_17,ui->widget_18,
                      ui->widget_19,ui->widget_20,ui->widget_21,ui->widget_22,ui->widget_23,ui->widget_24};

    for(int i=0; i<24; ++i) {
        mWid[i] = new ZTest_SwItemWid(wid[i]);
        mWid[i]->init(i);
    }


    mSnmp = new ZTest_SnmpThread(this);
    connect(mSnmp, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));

    mRtu = new ZTest_RtuThread(this);
    mRtu->mReg = mReg;
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}

void ZTest_SwWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void ZTest_SwWid::on_checkBox_clicked(bool checked)
{
    for(int i=0; i<24; ++i) {
        mWid[i]->setSelect(checked);
    }
}

void ZTest_SwWid::sendRtu(int i)
{
    sRtuSetCmd cmd;
    cmd.addr = ui->spinBox->value();
    cmd.reg = mReg + i;
    cmd.value = mWid[i]->status();
    mRtu->setCmd(cmd);
}

void ZTest_SwWid::sendSnmp(int i)
{
    sSnmpSetCmd cmd;
    int addr = ui->spinBox->value();
    QString oid = QString("%1.%2.%3.7.%4.0").arg(MIB_OID_CLEVER).arg(Z_MIB_OID).arg(addr).arg(i+1);
    cmd.oid = oid;
    cmd.type = SNMP_STRING_TYPE;
    cmd.value.append( mWid[i]->status()==1 ? "ON":"OFF");
    mSnmp->setCmd(cmd);
}

void ZTest_SwWid::on_pushButton_clicked()
{
    sConfigItem *item = Z_ConfigFile::bulid()->item;
    for(int i=0; i<24; ++i) {
        if(mWid[i]->select()) {
            if(item->setMode == Test_SNMP) {
                sendSnmp(i);  // 增加SNMP命令
            } else {
                sendRtu(i);
            }
        }
    }

    mSnmp->start();
    mRtu->start();

    ui->textEdit->clear();
}

void ZTest_SwWid::on_openRadio_clicked(bool checked)
{
    ui->closeRadio->setChecked(false);
    for(int i=0; i<24; ++i) {
        mWid[i]->setOpen(checked);
    }
}

void ZTest_SwWid::on_closeRadio_clicked(bool checked)
{
    ui->openRadio->setChecked(false);
    for(int i=0; i<24; ++i) {
        mWid[i]->setClose(checked);
    }
}
