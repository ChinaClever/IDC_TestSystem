#include "sisetmodbuscmddlg.h"
#include "ui_sisetmodbuscmddlg.h"
#include "si_com/siconfigfile.h"

SiSetModbusCmdDlg::SiSetModbusCmdDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SiSetModbusCmdDlg)
{
    ui->setupUi(this);
    initWid();
}

SiSetModbusCmdDlg::~SiSetModbusCmdDlg()
{
    delete ui;
}


void SiSetModbusCmdDlg::initWid()
{
    SiConfigFile *config = SiConfigFile::bulid();
    int num = config->item->cmdModel;

    switch (num) {
    case 1: ui->radioButton_1->setChecked(true);  break;
    case 2: ui->radioButton_2->setChecked(true);  break;
    default:
        break;
    }

}

int SiSetModbusCmdDlg::getCmdNum()
{
    int ret = 1;
    if(ui->radioButton_1->isChecked()) {
        ret = 1;
    } else if(ui->radioButton_2->isChecked()) {
        ret = 2;
    }

    return ret;
}
