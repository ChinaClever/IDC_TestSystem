
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/eload_mainwid.h \
    $$PWD/eload_toolbox/eload_toolboxwid.h \
    $$PWD/eload_com/in_datapackets.h \
    $$PWD/eload_rtu/in_rtupacket.h \
    $$PWD/eload_rtu/in_rturecv.h \
    $$PWD/eload_rtu/in_rtusent.h \
    $$PWD/eload_rtu/in_rtuthread.h \
    $$PWD/eload_rtu/in_rtutrans.h \
    $$PWD/eload_input/in_tablewid/in_envtablewid.h \
    $$PWD/eload_input/in_tablewid/in_inputtablewid.h \
    $$PWD/eload_input/in_tablewid/in_inputthresholdtablewid.h \
    $$PWD/eload_input/in_tablewid/in_transtablewid.h \
    $$PWD/eload_input/in_set/in_setenvwid.h \
    $$PWD/eload_input/in_set/in_setmainwid.h \
    $$PWD/eload_input/in_set/in_setthresholdwid.h \
    $$PWD/eload_input/in_mainwid.h \
    $$PWD/eload_home/eload_inputunitwid.h \
    $$PWD/eload_rtu/eload_rtusent.h \
    $$PWD/eload_home/eload_inputhomewid.h \
    $$PWD/eload_home/eload_statushomewid.h \
    $$PWD/eload_home/eload_homemainwid.h \
    $$PWD/eload_toolbox/eload_inputtoolwid.h \
    $$PWD/eload_toolbox/eload_hometoolwid.h \
    $$PWD/eload_com/eload_configfile.h \
    $$PWD/eload_toolbox/eload_settingtoolwid.h \
    $$PWD/eload_toolbox/eload_logstoolwid.h \
    $$PWD/eload_sql/eload_dbalarm.h \
    $$PWD/eload_sql/eload_dbenv.h \
    $$PWD/eload_sql/eload_dbmodbuscmd.h \
    $$PWD/eload_sql/eload_dbmodbustrans.h \
    $$PWD/eload_sql/eload_dblinerecords.h \
    $$PWD/eload_sql/eload_dblinethresholds.h \
    $$PWD/eload_logs/eload_logalarmwid.h \
    $$PWD/eload_logs/eload_logenvwid.h \
    $$PWD/eload_logs/eload_loglinerecordwid.h \
    $$PWD/eload_logs/eload_loglinethresholdwid.h \
    $$PWD/eload_logs/eload_logmodbuscmdwid.h \
    $$PWD/eload_logs/eload_logmodbustranswid.h \
    $$PWD/eload_logs/eload_logswid.h

	
SOURCES += \
    $$PWD/eload_mainwid.cpp \
    $$PWD/eload_toolbox/eload_toolboxwid.cpp \
    $$PWD/eload_com/in_datapackets.cpp \
    $$PWD/eload_rtu/in_rturecv.cpp \
    $$PWD/eload_rtu/in_rtusent.cpp \
    $$PWD/eload_rtu/in_rtuthread.cpp \
    $$PWD/eload_rtu/in_rtutrans.cpp \
    $$PWD/eload_input/in_tablewid/in_envtablewid.cpp \
    $$PWD/eload_input/in_tablewid/in_inputtablewid.cpp \
    $$PWD/eload_input/in_tablewid/in_inputthresholdtablewid.cpp \
    $$PWD/eload_input/in_tablewid/in_transtablewid.cpp \
    $$PWD/eload_input/in_set/in_setenvwid.cpp \
    $$PWD/eload_input/in_set/in_setmainwid.cpp \
    $$PWD/eload_input/in_set/in_setthresholdwid.cpp \
    $$PWD/eload_input/in_mainwid.cpp \
    $$PWD/eload_home/eload_inputunitwid.cpp \
    $$PWD/eload_rtu/eload_rtusent.cpp \
    $$PWD/eload_home/eload_inputhomewid.cpp \
    $$PWD/eload_home/eload_statushomewid.cpp \
    $$PWD/eload_home/eload_homemainwid.cpp \
    $$PWD/eload_toolbox/eload_inputtoolwid.cpp \
    $$PWD/eload_toolbox/eload_hometoolwid.cpp \
    $$PWD/eload_com/eload_configfile.cpp \
    $$PWD/eload_toolbox/eload_settingtoolwid.cpp \
    $$PWD/eload_toolbox/eload_logstoolwid.cpp \
    $$PWD/eload_sql/eload_dbalarm.cpp \
    $$PWD/eload_sql/eload_dbenv.cpp \
    $$PWD/eload_sql/eload_dbmodbuscmd.cpp \
    $$PWD/eload_sql/eload_dbmodbustrans.cpp \
    $$PWD/eload_sql/eload_dblinerecords.cpp \
    $$PWD/eload_sql/eload_dblinethresholds.cpp \
    $$PWD/eload_logs/eload_logalarmwid.cpp \
    $$PWD/eload_logs/eload_logenvwid.cpp \
    $$PWD/eload_logs/eload_loglinerecordwid.cpp \
    $$PWD/eload_logs/eload_loglinethresholdwid.cpp \
    $$PWD/eload_logs/eload_logmodbuscmdwid.cpp \
    $$PWD/eload_logs/eload_logmodbustranswid.cpp \
    $$PWD/eload_logs/eload_logswid.cpp

FORMS += \
    $$PWD/eload_mainwid.ui \
    $$PWD/eload_toolbox/eload_toolboxwid.ui \
    $$PWD/eload_input/in_set/in_setenvwid.ui \
    $$PWD/eload_input/in_set/in_setmainwid.ui \
    $$PWD/eload_input/in_set/in_setthresholdwid.ui \
    $$PWD/eload_input/in_mainwid.ui \
    $$PWD/eload_home/eload_inputunitwid.ui \
    $$PWD/eload_home/eload_inputhomewid.ui \
    $$PWD/eload_home/eload_statushomewid.ui \
    $$PWD/eload_home/eload_homemainwid.ui \
    $$PWD/eload_toolbox/eload_inputtoolwid.ui \
    $$PWD/eload_toolbox/eload_hometoolwid.ui \
    $$PWD/eload_toolbox/eload_settingtoolwid.ui \
    $$PWD/eload_toolbox/eload_logstoolwid.ui \
    $$PWD/eload_logs/eload_logswid.ui





