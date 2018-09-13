#include "si_logstoolwid.h"

SI_LogsToolWid::SI_LogsToolWid(QWidget *parent) : LogsToolWid(parent)
{
    config = SiConfigFile::bulid();
    sipdu();
}
