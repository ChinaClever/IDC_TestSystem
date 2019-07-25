#include "rset_thresholdoutputwid.h"
#include "ui_rset_thresholdoutputwid.h"

RSet_ThresholdOutputWid::RSet_ThresholdOutputWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSet_ThresholdOutputWid)
{
    ui->setupUi(this);
    mReg = R_RtuReg_OutputCurMin;
}

RSet_ThresholdOutputWid::~RSet_ThresholdOutputWid()
{
    delete ui;
}
int RSet_ThresholdOutputWid::getReg(int mode)
{
    int reg=R_RtuReg_OutputCurMin;

    switch (mode) {
    case Rpdu_Rtu_Test_min: reg = R_RtuReg_OutputCurMin; break;
//    case Rpdu_Rtu_Test_crMin: reg = 0X8000; break;
//    case Rpdu_Rtu_Test_crMax: reg = 0X8000; break;
    case Rpdu_Rtu_Test_max: reg = R_RtuReg_OutputCurMax; break;
    default: break;
    }

    return reg;
}
QString RSet_ThresholdOutputWid::getOid(int mode)
{
    int addr = ui->spinBox->value();
    QString oid = QString("%1.%2.%3.1").arg(MIB_OID_CLEVER).arg(R_MIB_OID).arg(addr);

    switch (mode) {
    case Rpdu_Rtu_Test_min: oid += QString(".%1").arg(11); break;
//    case Rpdu_Rtu_Test_crMin: oid += QString(".%1").arg(index + 1); break;
//    case Rpdu_Rtu_Test_crMax: oid += QString(".%1").arg(index + 2); break;
    case Rpdu_Rtu_Test_max: oid += QString(".%1").arg(12); break;
    default: oid += QString(".%1").arg(11);break;
    }

    return oid;
}

void RSet_ThresholdOutputWid::initwid(int mode)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3, ui->widget_4, ui->widget_5,ui->widget_6,
                      ui->widget_7, ui->widget_8, ui->widget_9, ui->widget_10, ui->widget_11, ui->widget_12,
                      ui->widget_13,ui->widget_14, ui->widget_15, ui->widget_16,ui->widget_17,ui->widget_18,
                      ui->widget_19,ui->widget_20,ui->widget_21,ui->widget_22,ui->widget_23,ui->widget_24};

    for(int i=0; i<24; ++i) {
        mWid[i] = new RSet_ThresholdItemWid(wid[i]);
        mWid[i]->initOutput(i, mode);
    }

    mOid = getOid(mode);
    mSnmp = new RSet_SnmpThread(this);
    connect(mSnmp, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));

    mReg = getReg(mode);
    mRtu = new RSet_RtuThread(this);
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
    mRtu->mReg = mReg;
}

void RSet_ThresholdOutputWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void RSet_ThresholdOutputWid::on_checkBox_clicked(bool checked)
{
    for(int i=0; i<24; ++i) {
        mWid[i]->setSelect(checked);
    }
    on_curSpinBox_valueChanged(ui->curSpinBox->value());
}


void RSet_ThresholdOutputWid::sendRtu(int i)
{
    sRtuSetCmd cmd;
    cmd.addr = ui->spinBox->value();
    cmd.reg = mReg + i;
    cmd.value = mWid[i]->status()*10;
    mRtu->setCmd(cmd);
}

void RSet_ThresholdOutputWid::sendSnmp(int i)
{
    sSnmpSetCmd cmd;
    cmd.oid = mOid + QString(".%1.0").arg(i+1);
    cmd.type = SNMP_STRING_TYPE;
    cmd.value.append( QString("%1.0").arg(mWid[i]->status()));
    mSnmp->setCmd(cmd);
}
void RSet_ThresholdOutputWid::on_pushButton_clicked()
{
    sConfigItem *item = R_ConfigFile::bulid()->item;
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


void RSet_ThresholdOutputWid::on_curSpinBox_valueChanged(int arg1)
{
    if(ui->checkBox->isChecked())
    {
        for(int i=0; i<24; ++i)
            mWid[i]->setValue(arg1);
    }
}
