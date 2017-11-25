#include "sisetdevnumdlg.h"
#include "ui_sisetdevnumdlg.h"
#include "si_com/siconfigfile.h"

SiSetDevNumDlg::SiSetDevNumDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SiSetDevNumDlg)
{
    ui->setupUi(this);
    initWid();
}

SiSetDevNumDlg::~SiSetDevNumDlg()
{
    delete ui;
}

void SiSetDevNumDlg::initWid()
{
    SiConfigFile *config = SiConfigFile::bulid();
    int num = config->item->devNum;
    ui->spinBox->setValue(num);
}

int SiSetDevNumDlg::getNum()
{
    return ui->spinBox->value();
}
