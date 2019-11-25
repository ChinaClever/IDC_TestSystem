
INCLUDEPATH += $$PWD

#include(mpduv1_test/mpduv1_test.pri)

HEADERS += \
    $$PWD/mpduv1_mainwid.h \
    $$PWD/mv1_toolbox/mpduv1_toolboxwid.h \
    $$PWD/mv1_rtu/mv1_rturecv.h \
    $$PWD/mv1_rtu/mv1_rtusent.h \
    $$PWD/mv1_rtu/mv1_rturegenum.h \
    $$PWD/mv1_rtu/mv1_rtutrans.h \
    $$PWD/mv1_com/mv1_datapackets.h \
    $$PWD/mv1_com/mv1_configfile.h \
    $$PWD/mv1_toolbox/mv1_logstoolwid.h \
    $$PWD/mv1_toolbox/mv1_settingtoolwid.h \
    $$PWD/mv1_sql/mv1_dbalarm.h \
    $$PWD/mv1_sql/mv1_dbenv.h \
    $$PWD/mv1_sql/mv1_dbmodbuscmd.h \
    $$PWD/mv1_sql/mv1_dbmodbustrans.h \
    $$PWD/mv1_sql/mv1_dblinerecords.h \
    $$PWD/mv1_sql/mv1_dblinethresholds.h \
    $$PWD/mv1_sql/mv1_dboutputrecords.h \
    $$PWD/mv1_dp/mv1_dpsavelinethreshold.h \
    $$PWD/mv1_dp/mv1_dpsaveoutput.h \
    $$PWD/mv1_dp/mv1_dpthread.h \
    $$PWD/mv1_logs/mv1_logalarmwid.h \
    $$PWD/mv1_logs/mv1_logenvwid.h \
    $$PWD/mv1_logs/mv1_logmodbuscmdwid.h \
    $$PWD/mv1_logs/mv1_logmodbustranswid.h \
    $$PWD/mv1_logs/mv1_loglinerecordwid.h \
    $$PWD/mv1_logs/mv1_loglinethresholdwid.h \
    $$PWD/mv1_logs/mv1_logoutputrecordwid.h \
    $$PWD/mv1_logs/mv1_logswid.h \
    $$PWD/mv1_service/json/mv1_buildjson.h \
    $$PWD/mv1_service/mv1_servicethread.h \
    $$PWD/mv1_dp/mv1_dpalarmsave.h \
    $$PWD/mv1_dp/mv1_dpsaveenv.h \
    $$PWD/mv1_dp/mv1_dpsavelinerecord.h \
    $$PWD/mv1_dp/mv1_dpsavetrans.h \
    $$PWD/mv1_toolbox/mv1_statustoolwid.h \
    $$PWD/mv1_toolbox/mv1_modetoolwid.h \
    $$PWD/mv1_rtu/mv1_rtuthread.h \
    $$PWD/mv1_status/mv1_statuswid.h \
    $$PWD/mv1_snmp/mv1_snmpsend.h \
    $$PWD/mv1_snmp/mv1_snmprecv.h \
    $$PWD/mv1_snmp/mv1_snmptrans.h \
    $$PWD/mv1_setting/mv1_setsnmp/mv1set_snmpthread.h \
    $$PWD/mv1_setting/mv1_setrtu/mv1set_rtuthread.h \
    $$PWD/mv1_setting/mv1_setele/mv1set_eleitemwid.h \
    $$PWD/mv1_setting/mv1_setele/mv1set_outputelewid.h \
    $$PWD/mv1_setting/mv1_setenv/mv1set_envitemwid.h \
    $$PWD/mv1_setting/mv1_setenv/mv1set_envunitwid.h \
    $$PWD/mv1_setting/mv1_setenv/mv1set_envwid.h \
    $$PWD/mv1_setting/mv1_setline/mv1set_lineitemwid.h \
    $$PWD/mv1_setting/mv1_setline/mv1set_lineunitwid.h \
    $$PWD/mv1_setting/mv1_setline/mv1set_linewid.h \
    $$PWD/mv1_setting/mv1_setsw/mv1set_switemwid.h \
    $$PWD/mv1_setting/mv1_setsw/mv1set_swwid.h \
    $$PWD/mv1_setting/mv1_setswcycle/mv1set_swcycleitemwid.h \
    $$PWD/mv1_setting/mv1_setswcycle/mv1set_swcyclewid.h \
    $$PWD/mv1_setting/mv1_setthreshold/mv1set_thresholditemwid.h \
    $$PWD/mv1_setting/mv1_setthreshold/mv1set_thresholdoutputwid.h \
    $$PWD/mv1_setting/mv1set_mainwid.h \
    $$PWD/mv1_test/mv1test_config.h \
    $$PWD/mv1_test/mv1test_transthread.h \
    $$PWD/mv1_test/mv1test_corethread.h \
    $$PWD/mv1_test/mv1test_mainwid.h

	
SOURCES += \
    $$PWD/mpduv1_mainwid.cpp \
    $$PWD/mv1_toolbox/mpduv1_toolboxwid.cpp \
    $$PWD/mv1_rtu/mv1_rturecv.cpp \
    $$PWD/mv1_rtu/mv1_rtusent.cpp \
    $$PWD/mv1_rtu/mv1_rtutrans.cpp \
    $$PWD/mv1_com/mv1_datapackets.cpp \
    $$PWD/mv1_com/mv1_configfile.cpp \
    $$PWD/mv1_toolbox/mv1_logstoolwid.cpp \
    $$PWD/mv1_toolbox/mv1_settingtoolwid.cpp \
    $$PWD/mv1_sql/mv1_dbalarm.cpp \
    $$PWD/mv1_sql/mv1_dbenv.cpp \
    $$PWD/mv1_sql/mv1_dbmodbuscmd.cpp \
    $$PWD/mv1_sql/mv1_dbmodbustrans.cpp \
    $$PWD/mv1_sql/mv1_dblinerecords.cpp \
    $$PWD/mv1_sql/mv1_dblinethresholds.cpp \
    $$PWD/mv1_sql/mv1_dboutputrecords.cpp \
    $$PWD/mv1_dp/mv1_dpsavelinethreshold.cpp \
    $$PWD/mv1_dp/mv1_dpsaveoutput.cpp \
    $$PWD/mv1_dp/mv1_dpthread.cpp \
    $$PWD/mv1_logs/mv1_logalarmwid.cpp \
    $$PWD/mv1_logs/mv1_logenvwid.cpp \
    $$PWD/mv1_logs/mv1_logmodbuscmdwid.cpp \
    $$PWD/mv1_logs/mv1_logmodbustranswid.cpp \
    $$PWD/mv1_logs/mv1_loglinerecordwid.cpp \
    $$PWD/mv1_logs/mv1_loglinethresholdwid.cpp \
    $$PWD/mv1_logs/mv1_logoutputrecordwid.cpp \
    $$PWD/mv1_logs/mv1_logswid.cpp \
    $$PWD/mv1_service/json/mv1_buildjson.cpp \
    $$PWD/mv1_service/mv1_servicethread.cpp \
    $$PWD/mv1_dp/mv1_dpalarmsave.cpp \
    $$PWD/mv1_dp/mv1_dpsaveenv.cpp \
    $$PWD/mv1_dp/mv1_dpsavelinerecord.cpp \
    $$PWD/mv1_dp/mv1_dpsavetrans.cpp \
    $$PWD/mv1_toolbox/mv1_statustoolwid.cpp \
    $$PWD/mv1_toolbox/mv1_modetoolwid.cpp \
    $$PWD/mv1_rtu/mv1_rtuthread.cpp \
    $$PWD/mv1_status/mv1_statuswid.cpp \
    $$PWD/mv1_snmp/mv1_snmpsend.cpp \
    $$PWD/mv1_snmp/mv1_snmprecv.cpp \
    $$PWD/mv1_snmp/mv1_snmptrans.cpp \
    $$PWD/mv1_setting/mv1_setsnmp/mv1set_snmpthread.cpp \
    $$PWD/mv1_setting/mv1_setrtu/mv1set_rtuthread.cpp \
    $$PWD/mv1_setting/mv1_setele/mv1set_eleitemwid.cpp \
    $$PWD/mv1_setting/mv1_setele/mv1set_outputelewid.cpp \
    $$PWD/mv1_setting/mv1_setenv/mv1set_envitemwid.cpp \
    $$PWD/mv1_setting/mv1_setenv/mv1set_envunitwid.cpp \
    $$PWD/mv1_setting/mv1_setenv/mv1set_envwid.cpp \
    $$PWD/mv1_setting/mv1_setline/mv1set_lineitemwid.cpp \
    $$PWD/mv1_setting/mv1_setline/mv1set_lineunitwid.cpp \
    $$PWD/mv1_setting/mv1_setline/mv1set_linewid.cpp \
    $$PWD/mv1_setting/mv1_setsw/mv1set_switemwid.cpp \
    $$PWD/mv1_setting/mv1_setsw/mv1set_swwid.cpp \
    $$PWD/mv1_setting/mv1_setswcycle/mv1set_swcycleitemwid.cpp \
    $$PWD/mv1_setting/mv1_setswcycle/mv1set_swcyclewid.cpp \
    $$PWD/mv1_setting/mv1_setthreshold/mv1set_thresholditemwid.cpp \
    $$PWD/mv1_setting/mv1_setthreshold/mv1set_thresholdoutputwid.cpp \
    $$PWD/mv1_setting/mv1set_mainwid.cpp \
    $$PWD/mv1_test/mv1test_config.cpp \
    $$PWD/mv1_test/mv1test_transthread.cpp \
    $$PWD/mv1_test/mv1test_corethread.cpp \
    $$PWD/mv1_test/mv1test_mainwid.cpp

FORMS += \
    $$PWD/mpduv1_mainwid.ui \
    $$PWD/mv1_logs/mv1_logswid.ui \
    $$PWD/mv1_setting/mv1set_mainwid.ui \
    $$PWD/mv1_status/mv1_statuswid.ui \
    $$PWD/mv1_setting/mv1_setele/mv1set_eleitemwid.ui \
    $$PWD/mv1_setting/mv1_setele/mv1set_outputelewid.ui \
    $$PWD/mv1_setting/mv1_setenv/mv1set_envitemwid.ui \
    $$PWD/mv1_setting/mv1_setenv/mv1set_envunitwid.ui \
    $$PWD/mv1_setting/mv1_setenv/mv1set_envwid.ui \
    $$PWD/mv1_setting/mv1_setline/mv1set_lineitemwid.ui \
    $$PWD/mv1_setting/mv1_setline/mv1set_lineunitwid.ui \
    $$PWD/mv1_setting/mv1_setline/mv1set_linewid.ui \
    $$PWD/mv1_setting/mv1_setsw/mv1set_switemwid.ui \
    $$PWD/mv1_setting/mv1_setsw/mv1set_swwid.ui \
    $$PWD/mv1_setting/mv1_setswcycle/mv1set_swcycleitemwid.ui \
    $$PWD/mv1_setting/mv1_setswcycle/mv1set_swcyclewid.ui \
    $$PWD/mv1_setting/mv1_setthreshold/mv1set_thresholditemwid.ui \
    $$PWD/mv1_setting/mv1_setthreshold/mv1set_thresholdoutputwid.ui





