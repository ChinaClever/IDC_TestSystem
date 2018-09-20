#include "ztest_thresholdoutputwid.h"
#include "ui_ztest_thresholdoutputwid.h"

ZTest_ThresholdOutputWid::ZTest_ThresholdOutputWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZTest_ThresholdOutputWid)
{
    ui->setupUi(this);
    mReg = Z_RtuReg_OutputCurMin;
}

ZTest_ThresholdOutputWid::~ZTest_ThresholdOutputWid()
{
    delete ui;
}
int ZTest_ThresholdOutputWid::getReg(int mode)
{
    int reg=Z_RtuReg_OutputCurMin;

    switch (mode) {
    case Zpdu_Rtu_Test_min: reg = Z_RtuReg_OutputCurMin; break;
    case Zpdu_Rtu_Test_crMin: reg = Z_RtuReg_OutputCurCrMin; break;
    case Zpdu_Rtu_Test_crMax: reg = Z_RtuReg_OutputCurCrMax; break;
    case Zpdu_Rtu_Test_max: reg = Z_RtuReg_OutputCurMax; break;
    default: break;
    }

    return reg;
}

void ZTest_ThresholdOutputWid::initwid(int mode)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3, ui->widget_4, ui->widget_5,ui->widget_6,
                      ui->widget_7, ui->widget_8, ui->widget_9, ui->widget_10, ui->widget_11, ui->widget_12,
                      ui->widget_13,ui->widget_14, ui->widget_15, ui->widget_16,ui->widget_17,ui->widget_18,
                      ui->widget_19,ui->widget_20,ui->widget_21,ui->widget_22,ui->widget_23,ui->widget_24};

    for(int i=0; i<24; ++i) {
        mWid[i] = new ZTest_ThresholdItemWid(wid[i]);
        mWid[i]->initOutput(i, mode);
    }

    mReg = getReg(mode);
    mRtu = new ZTest_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
    mRtu->mReg = mReg;
}

void ZTest_ThresholdOutputWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void ZTest_ThresholdOutputWid::on_checkBox_clicked(bool checked)
{
    for(int i=0; i<24; ++i) {
        mWid[i]->setSelect(checked);
    }
    on_curSpinBox_valueChanged(ui->curSpinBox->value());
}

void ZTest_ThresholdOutputWid::on_pushButton_clicked()
{
    for(int i=0; i<24; ++i) {
        if(mWid[i]->select()) {
            sZTestRtuSetCmd cmd;
            cmd.addr = ui->spinBox->value();
            cmd.reg = mReg + i;
            cmd.value = mWid[i]->status();
            mRtu->setCmd(cmd);
        }
    }

    mRtu->start();
    ui->textEdit->clear();
}


void ZTest_ThresholdOutputWid::on_curSpinBox_valueChanged(int arg1)
{
    if(ui->checkBox->isChecked())
    {
        for(int i=0; i<24; ++i)
            mWid[i]->setValue(arg1);
    }
}
