
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/si_rtu/si_rtu_sent.h \
    $$PWD/si_rtu/si_rtu_recv.h \
    $$PWD/si_rtu/si_rtu_setcmd.h \
    $$PWD/si_rtu/si_rtuthread.h \
    $$PWD/simainwid.h \
    $$PWD/toolbox/sitoolboxwid.h \
    $$PWD/toolbox/sisimulationtoolwid.h \
    $$PWD/toolbox/sitesttoolwid.h \
    $$PWD/toolbox/sisettingtoolwid.h \
    $$PWD/toolbox/sisetlinenum.h \
    $$PWD/toolbox/sisetdevnumdlg.h \
    $$PWD/toolbox/sisetmodbuscmddlg.h \
    $$PWD/si_com/sidatapackets.h \
    $$PWD/si_com/siconfigfile.h \
    $$PWD/si_simulate/si_simulatethread.h \
    $$PWD/toolbox/sisetmodbustimedlg.h \
    $$PWD/toolbox/silogstoolwid.h \
    $$PWD/si_simulate/si_envtablewid.h \
    $$PWD/si_simulate/si_thresholdtablewid.h \
    $$PWD/si_simulate/si_transtablewid.h \
    $$PWD/si_simulate/si_devtablewid.h \
    $$PWD/toolbox/silogstimetooldlg.h \
    $$PWD/si_logsthread/si_translogthread.h \
    $$PWD/si_logsthread/si_comlogthread.h \
    $$PWD/si_logsthread/si_envlogthread.h \
    $$PWD/si_logsthread/si_recordlogthread.h \
    $$PWD/si_logsthread/si_thresholdlogthread.h \
    $$PWD/si_logsthread/si_alarmlogthread.h \
    $$PWD/si_setting/si_setmainwid.h \
    $$PWD/si_setting/si_addrsetwid.h \
    $$PWD/si_setting/si_unitsetwid.h \
    $$PWD/si_setting/si_thresholdsetwid.h \
    $$PWD/si_setting/si_elesetwid.h \
    $$PWD/si_logs/silogmodbuscmdwid.h \
    $$PWD/si_logs/silogmodbustranswid.h \
    $$PWD/si_logs/silogenvwid.h \
    $$PWD/si_logs/silogrealrecordwid.h \
    $$PWD/si_logs/silogthresholdwid.h \
    $$PWD/si_logs/silogalarmwid.h \
    $$PWD/si_sql/sidbmodbuscmd.h \
    $$PWD/si_sql/sidbmodbustrans.h \
    $$PWD/si_sql/sidbenv.h \
    $$PWD/si_sql/sidbrealrecords.h \
    $$PWD/si_sql/sidbthresholds.h \
    $$PWD/si_sql/sidbalarm.h \
    $$PWD/si_service/json/si_buildjson.h \
    $$PWD/si_service/si_servicethread.h

	
SOURCES += \
    $$PWD/si_rtu/si_rtu_sent.cpp \
    $$PWD/si_rtu/si_rtu_recv.cpp \
    $$PWD/si_rtu/si_rtuthread.cpp \
    $$PWD/simainwid.cpp \
    $$PWD/toolbox/sitoolboxwid.cpp \
    $$PWD/toolbox/sisimulationtoolwid.cpp \
    $$PWD/toolbox/sitesttoolwid.cpp \
    $$PWD/toolbox/sisettingtoolwid.cpp \
    $$PWD/toolbox/sisetlinenum.cpp \
    $$PWD/toolbox/sisetdevnumdlg.cpp \
    $$PWD/toolbox/sisetmodbuscmddlg.cpp \
    $$PWD/si_com/sidatapackets.cpp \
    $$PWD/si_com/siconfigfile.cpp \
    $$PWD/si_simulate/si_simulatethread.cpp \
    $$PWD/toolbox/sisetmodbustimedlg.cpp \
    $$PWD/toolbox/silogstoolwid.cpp \
    $$PWD/si_simulate/si_envtablewid.cpp \
    $$PWD/si_simulate/si_thresholdtablewid.cpp \
    $$PWD/si_simulate/si_transtablewid.cpp \
    $$PWD/si_simulate/si_devtablewid.cpp \
    $$PWD/toolbox/silogstimetooldlg.cpp \
    $$PWD/si_logsthread/si_translogthread.cpp \
    $$PWD/si_logsthread/si_comlogthread.cpp \
    $$PWD/si_logsthread/si_envlogthread.cpp \
    $$PWD/si_logsthread/si_recordlogthread.cpp \
    $$PWD/si_logsthread/si_thresholdlogthread.cpp \
    $$PWD/si_logsthread/si_alarmlogthread.cpp \
    $$PWD/si_setting/si_setmainwid.cpp \
    $$PWD/si_setting/si_addrsetwid.cpp \
    $$PWD/si_setting/si_unitsetwid.cpp \
    $$PWD/si_setting/si_thresholdsetwid.cpp \
    $$PWD/si_setting/si_elesetwid.cpp \
    $$PWD/si_logs/silogmodbuscmdwid.cpp \
    $$PWD/si_logs/silogmodbustranswid.cpp \
    $$PWD/si_logs/silogenvwid.cpp \
    $$PWD/si_logs/silogrealrecordwid.cpp \
    $$PWD/si_logs/silogthresholdwid.cpp \
    $$PWD/si_logs/silogalarmwid.cpp \
    $$PWD/si_sql/sidbmodbuscmd.cpp \
    $$PWD/si_sql/sidbmodbustrans.cpp \
    $$PWD/si_sql/sidbenv.cpp \
    $$PWD/si_sql/sidbrealrecords.cpp \
    $$PWD/si_sql/sidbthresholds.cpp \
    $$PWD/si_sql/sidbalarm.cpp \
    $$PWD/si_service/json/si_buildjson.cpp \
    $$PWD/si_service/si_servicethread.cpp

FORMS += \
    $$PWD/simainwid.ui \
    $$PWD/toolbox/sitoolboxwid.ui \
    $$PWD/toolbox/sisimulationtoolwid.ui \
    $$PWD/toolbox/sitesttoolwid.ui \
    $$PWD/toolbox/sisettingtoolwid.ui \
    $$PWD/toolbox/sisetlinenum.ui \
    $$PWD/toolbox/sisetdevnumdlg.ui \
    $$PWD/toolbox/sisetmodbuscmddlg.ui \
    $$PWD/toolbox/sisetmodbustimedlg.ui \
    $$PWD/toolbox/silogstoolwid.ui \
    $$PWD/toolbox/silogstimetooldlg.ui \
    $$PWD/si_setting/si_setmainwid.ui \
    $$PWD/si_setting/si_addrsetwid.ui \
    $$PWD/si_setting/si_unitsetwid.ui \
    $$PWD/si_setting/si_thresholdsetwid.ui \
    $$PWD/si_setting/si_elesetwid.ui





