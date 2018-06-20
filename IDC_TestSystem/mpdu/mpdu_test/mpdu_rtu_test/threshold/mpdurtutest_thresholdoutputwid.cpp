#include "mpdurtutest_thresholdoutputwid.h"
#include "ui_mpdurtutest_thresholdoutputwid.h"

MpduRtuTest_ThresholdOutputWid::MpduRtuTest_ThresholdOutputWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MpduRtuTest_ThresholdOutputWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
    mReg = 157;
}

MpduRtuTest_ThresholdOutputWid::~MpduRtuTest_ThresholdOutputWid()
{
    delete ui;
}


void MpduRtuTest_ThresholdOutputWid::initwid(int mode, SerialPort *serial)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3, ui->widget_4, ui->widget_5,ui->widget_6,
                      ui->widget_7, ui->widget_8, ui->widget_9, ui->widget_10, ui->widget_11, ui->widget_12,
                      ui->widget_13,ui->widget_14, ui->widget_15, ui->widget_16,ui->widget_17,ui->widget_18,
                      ui->widget_19,ui->widget_20,ui->widget_21,ui->widget_22,ui->widget_23,ui->widget_24};

    for(int i=0; i<24; ++i) {
        mWid[i] = new MpduRtuTest_ThresholdItemWid(wid[i]);
        mWid[i]->init(i, mode);
    }

    if(mode) mReg = 229;
    mRtu = new MpduRtuTestThread(this);
    mRtu->init(serial);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
    mRtu->mReg = mReg;
}

void MpduRtuTest_ThresholdOutputWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void MpduRtuTest_ThresholdOutputWid::on_checkBox_clicked(bool checked)
{
    for(int i=0; i<24; ++i) {
        mWid[i]->setSelect(checked);
    }
    on_curDoubleSpinBox_valueChanged(ui->curDoubleSpinBox->value());
}

void MpduRtuTest_ThresholdOutputWid::on_pushButton_clicked()
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


void MpduRtuTest_ThresholdOutputWid::on_curDoubleSpinBox_valueChanged(double arg1)
{
    if(ui->checkBox->isChecked())
    {
        for(int i=0; i<24; ++i)
            mWid[i]->setValue(arg1);
    }
}
