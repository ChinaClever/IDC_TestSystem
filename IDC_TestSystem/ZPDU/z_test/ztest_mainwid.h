#ifndef Z_TESTMAINWID_H
#define Z_TESTMAINWID_H
#include "testmainwid.h"
#include "z_com/z_datapackets.h"
#include "ztest_config.h"

class ZTest_MainWid : public TestMainWid
{
    Q_OBJECT

public:
    explicit ZTest_MainWid(QWidget *parent = 0);

};

#endif // Z_TESTMAINWID_H
