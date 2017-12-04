#include "silogstoolwid.h"
#include "ui_silogstoolwid.h"
#include "si_com/siconfigfile.h"
#include "silogstimetooldlg.h"

SiLogsToolWid::SiLogsToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SiLogsToolWid)
{
    ui->setupUi(this);
    initLogTime();
}

SiLogsToolWid::~SiLogsToolWid()
{
    delete ui;
}

void SiLogsToolWid::on_modbusBtn_clicked()
{
    emit logsSig(SI_Log_Modbus);
}



void SiLogsToolWid::updateLogTime(int num)
{
    SiConfigFile *config = SiConfigFile::bulid();
    config->item->logMins = num;

    QString str = QString::number(config->item->logMins) + tr("分钟");
    ui->timeLab->setText(str);
    config->setLogTime(num);
}

void SiLogsToolWid::initLogTime()
{
    SiConfigFile *config = SiConfigFile::bulid();
    int num = config->getLogTime();
    updateLogTime(num);
}

void SiLogsToolWid::on_timeBtn_clicked()
{
    SiLogsTimeToolDlg dlg(this);
    if(dlg.exec() == QDialog::Accepted) {
        int time = dlg.getTime();
        updateLogTime(time);
    }
}

void SiLogsToolWid::on_transBtn_clicked()
{
    emit logsSig(SI_Log_Trans);
}

void SiLogsToolWid::on_envBtn_clicked()
{
     emit logsSig(SI_Log_Env);
}
