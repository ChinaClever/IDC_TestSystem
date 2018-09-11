
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/z_rtu/z_rturegenum.h \
    $$PWD/z_rtu/z_rtusent.h \
    $$PWD/z_rtu/z_rturecv.h \
    $$PWD/z_rtu/z_rtutrans.h \
    $$PWD/z_com/z_configfile.h \
    $$PWD/z_com/z_datapackets.h \
    $$PWD/z_sql/z_dbalarm.h \
    $$PWD/z_sql/z_dbenv.h \
    $$PWD/z_sql/z_dblinerecords.h \
    $$PWD/z_sql/z_dblinethresholds.h \
    $$PWD/z_sql/z_dbmodbuscmd.h \
    $$PWD/z_sql/z_dbmodbustrans.h \
    $$PWD/z_sql/z_dboutputrecords.h \
    $$PWD/z_sql/z_dblooprecords.h \
    $$PWD/z_dp/z_dpalarmsave.h \
    $$PWD/z_dp/z_dpsaveenv.h \
    $$PWD/z_dp/z_dpsavelinerecord.h \
    $$PWD/z_dp/z_dpsavelinethreshold.h \
    $$PWD/z_dp/z_dpsaveoutput.h \
    $$PWD/z_dp/z_dpsaveloop.h \
    $$PWD/z_dp/z_dpsavetrans.h \
    $$PWD/z_dp/z_dpthread.h \
    $$PWD/z_logs/z_logalarmwid.h \
    $$PWD/z_logs/z_logenvwid.h \
    $$PWD/z_logs/z_loglinerecordwid.h \
    $$PWD/z_logs/z_loglinethresholdwid.h \
    $$PWD/z_logs/z_logmodbuscmdwid.h \
    $$PWD/z_logs/z_logmodbustranswid.h \
    $$PWD/z_logs/z_logoutputrecordwid.h \
    $$PWD/z_logs/z_loglooprecordwid.h \
    $$PWD/z_logs/z_logswid.h \
    $$PWD/z_service/json/z_buildjson.h \
    $$PWD/z_service/z_servicethread.h \
    $$PWD/z_simulate/z_simulatethread.h \
    $$PWD/z_simulate/z_simulatewid.h \
    $$PWD/z_toolbox/z_simulationtoolwid.h \
    $$PWD/z_toolbox/z_settingtoolwid.h \
    $$PWD/z_toolbox/z_logstoolwid.h \
    $$PWD/z_toolbox/z_toolboxwid.h \
    $$PWD/zpdu_mainwid.h \
    $$PWD/z_test/z_testrtu/ztest_rtuthread.h \
    $$PWD/z_test/z_testsw/ztest_switemwid.h \
    $$PWD/z_test/z_testsw/ztest_swwid.h \
    $$PWD/z_test/ztest_mainwid.h \
    $$PWD/z_test/z_testthreshold/ztest_thresholditemwid.h \
    $$PWD/z_test/z_testthreshold/ztest_thresholdoutputwid.h \
    $$PWD/z_test/z_testele/ztest_eleitemwid.h \
    $$PWD/z_test/z_testele/ztest_outputelewid.h \
    $$PWD/z_test/z_testline/ztest_lineitemwid.h \
    $$PWD/z_test/z_testline/ztest_lineunitwid.h \
    $$PWD/z_test/z_testline/ztest_linewid.h \
    $$PWD/z_test/z_testenv/ztest_envitemwid.h \
    $$PWD/z_test/z_testenv/ztest_envunitwid.h \
    $$PWD/z_test/z_testenv/ztest_envwid.h \
    $$PWD/z_test/z_testloop/ztest_loopitemwid.h \
    $$PWD/z_test/z_testloop/ztest_loopunitwid.h \
    $$PWD/z_test/z_testloop/ztest_loopwid.h \
    $$PWD/z_snmp/z_snmpthread.h \
    $$PWD/z_snmp/z_snmpsend.h \
    $$PWD/z_snmp/z_snmptrans.h \
    $$PWD/z_snmp/z_snmprecv.h

	
SOURCES += \
    $$PWD/z_rtu/z_rtusent.cpp \
    $$PWD/z_rtu/z_rturecv.cpp \
    $$PWD/z_rtu/z_rtutrans.cpp \
    $$PWD/z_com/z_configfile.cpp \
    $$PWD/z_com/z_datapackets.cpp \
    $$PWD/z_sql/z_dbalarm.cpp \
    $$PWD/z_sql/z_dbenv.cpp \
    $$PWD/z_sql/z_dblinerecords.cpp \
    $$PWD/z_sql/z_dblinethresholds.cpp \
    $$PWD/z_sql/z_dbmodbuscmd.cpp \
    $$PWD/z_sql/z_dbmodbustrans.cpp \
    $$PWD/z_sql/z_dboutputrecords.cpp \
    $$PWD/z_sql/z_dblooprecords.cpp \
    $$PWD/z_dp/z_dpalarmsave.cpp \
    $$PWD/z_dp/z_dpsaveenv.cpp \
    $$PWD/z_dp/z_dpsavelinerecord.cpp \
    $$PWD/z_dp/z_dpsavelinethreshold.cpp \
    $$PWD/z_dp/z_dpsaveoutput.cpp \
    $$PWD/z_dp/z_dpsaveloop.cpp \
    $$PWD/z_dp/z_dpsavetrans.cpp \
    $$PWD/z_dp/z_dpthread.cpp \
    $$PWD/z_logs/z_logalarmwid.cpp \
    $$PWD/z_logs/z_logenvwid.cpp \
    $$PWD/z_logs/z_loglinerecordwid.cpp \
    $$PWD/z_logs/z_loglinethresholdwid.cpp \
    $$PWD/z_logs/z_logmodbuscmdwid.cpp \
    $$PWD/z_logs/z_logmodbustranswid.cpp \
    $$PWD/z_logs/z_logoutputrecordwid.cpp \
    $$PWD/z_logs/z_loglooprecordwid.cpp \
    $$PWD/z_logs/z_logswid.cpp \
    $$PWD/z_service/json/z_buildjson.cpp \
    $$PWD/z_service/z_servicethread.cpp \
    $$PWD/z_simulate/z_simulatethread.cpp \
    $$PWD/z_simulate/z_simulatewid.cpp \
    $$PWD/z_toolbox/z_simulationtoolwid.cpp \
    $$PWD/z_toolbox/z_settingtoolwid.cpp \
    $$PWD/z_toolbox/z_logstoolwid.cpp \
    $$PWD/z_toolbox/z_toolboxwid.cpp \
    $$PWD/zpdu_mainwid.cpp \
    $$PWD/z_test/z_testrtu/ztest_rtuthread.cpp \
    $$PWD/z_test/z_testsw/ztest_switemwid.cpp \
    $$PWD/z_test/z_testsw/ztest_swwid.cpp \
    $$PWD/z_test/ztest_mainwid.cpp \
    $$PWD/z_test/z_testthreshold/ztest_thresholditemwid.cpp \
    $$PWD/z_test/z_testthreshold/ztest_thresholdoutputwid.cpp \
    $$PWD/z_test/z_testele/ztest_eleitemwid.cpp \
    $$PWD/z_test/z_testele/ztest_outputelewid.cpp \
    $$PWD/z_test/z_testline/ztest_lineitemwid.cpp \
    $$PWD/z_test/z_testline/ztest_lineunitwid.cpp \
    $$PWD/z_test/z_testline/ztest_linewid.cpp \
    $$PWD/z_test/z_testenv/ztest_envitemwid.cpp \
    $$PWD/z_test/z_testenv/ztest_envunitwid.cpp \
    $$PWD/z_test/z_testenv/ztest_envwid.cpp \
    $$PWD/z_test/z_testloop/ztest_loopitemwid.cpp \
    $$PWD/z_test/z_testloop/ztest_loopunitwid.cpp \
    $$PWD/z_test/z_testloop/ztest_loopwid.cpp \
    $$PWD/z_snmp/z_snmpthread.cpp \
    $$PWD/z_snmp/z_snmpsend.cpp \
    $$PWD/z_snmp/z_snmptrans.cpp \
    $$PWD/z_snmp/z_snmprecv.cpp

FORMS += \
    $$PWD/z_logs/z_logswid.ui \
    $$PWD/z_simulate/z_simulatewid.ui \
    $$PWD/z_toolbox/z_simulationtoolwid.ui \
    $$PWD/z_toolbox/z_settingtoolwid.ui \
    $$PWD/z_toolbox/z_logstoolwid.ui \
    $$PWD/z_toolbox/z_toolboxwid.ui \
    $$PWD/zpdu_mainwid.ui \
    $$PWD/z_test/z_testsw/ztest_switemwid.ui \
    $$PWD/z_test/z_testsw/ztest_swwid.ui \
    $$PWD/z_test/ztest_mainwid.ui \
    $$PWD/z_test/z_testthreshold/ztest_thresholditemwid.ui \
    $$PWD/z_test/z_testthreshold/ztest_thresholdoutputwid.ui \
    $$PWD/z_test/z_testele/ztest_eleitemwid.ui \
    $$PWD/z_test/z_testele/ztest_outputelewid.ui \
    $$PWD/z_test/z_testline/ztest_lineitemwid.ui \
    $$PWD/z_test/z_testline/ztest_lineunitwid.ui \
    $$PWD/z_test/z_testline/ztest_linewid.ui \
    $$PWD/z_test/z_testenv/ztest_envitemwid.ui \
    $$PWD/z_test/z_testenv/ztest_envunitwid.ui \
    $$PWD/z_test/z_testenv/ztest_envwid.ui \
    $$PWD/z_test/z_testloop/ztest_loopitemwid.ui \
    $$PWD/z_test/z_testloop/ztest_loopunitwid.ui \
    $$PWD/z_test/z_testloop/ztest_loopwid.ui





