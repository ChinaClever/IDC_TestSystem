#include "mpdurtutest_swwid.h"
#include "ui_mpdurtutest_swwid.h"

MpduRtuTest_SwWid::MpduRtuTest_SwWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MpduRtuTest_SwWid)
{
    ui->setupUi(this);
    mReg = 1003;
}

MpduRtuTest_SwWid::~MpduRtuTest_SwWid()
{
    delete ui;
}


void MpduRtuTest_SwWid::initwid(SerialPort *serial)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3, ui->widget_4, ui->widget_5,ui->widget_6,
                      ui->widget_7, ui->widget_8, ui->widget_9, ui->widget_10, ui->widget_11, ui->widget_12,
                      ui->widget_13,ui->widget_14, ui->widget_15, ui->widget_16,ui->widget_17,ui->widget_18,
                      ui->widget_19,ui->widget_20,ui->widget_21,ui->widget_22,ui->widget_23,ui->widget_24};

    for(int i=0; i<24; ++i) {
        mWid[i] = new MpduRtuTest_SwItemWid(wid[i]);
        mWid[i]->init(i);
    }

    mRtu = new MpduRtuTestThread(this);
    mRtu->init(serial);
    mRtu->mReg = mReg;
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}

void MpduRtuTest_SwWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void MpduRtuTest_SwWid::on_checkBox_clicked(bool checked)
{
    for(int i=0; i<24; ++i) {
        mWid[i]->setSelect(checked);
    }
}

void MpduRtuTest_SwWid::on_pushButton_clicked()
{
    for(int i=0; i<24; ++i) {
        if(mWid[i]->select()) {
            sMpduRtuTestSetCmd cmd;
            cmd.addr = ui->spinBox->value();
            cmd.reg = mReg + i;
            cmd.value = mWid[i]->status();
            mRtu->setCmd(cmd);
        }
    }

    mRtu->start();
    ui->textEdit->clear();
}

void MpduRtuTest_SwWid::on_openRadio_clicked(bool checked)
{
    ui->closeRadio->setChecked(false);
    for(int i=0; i<24; ++i) {
        mWid[i]->setOpen(checked);
    }
}

void MpduRtuTest_SwWid::on_closeRadio_clicked(bool checked)
{
    ui->openRadio->setChecked(false);
    for(int i=0; i<24; ++i) {
        mWid[i]->setClose(checked);
    }
}