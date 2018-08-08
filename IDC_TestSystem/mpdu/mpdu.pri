
INCLUDEPATH += $$PWD

#include(mpdu_test/mpdu_test.pri)

HEADERS += \
    $$PWD/mpdu_mainwid.h \
    $$PWD/m_toolbox/mpdu_toolboxwid.h \
    $$PWD/m_rtu/m_rturecv.h \
    $$PWD/m_rtu/m_rtusent.h \
    $$PWD/m_rtu/m_rturegenum.h \
    $$PWD/m_rtu/m_rtutrans.h \
    $$PWD/m_com/m_datapackets.h \
    $$PWD/m_com/m_configfile.h \
    $$PWD/m_toolbox/m_logstoolwid.h \
    $$PWD/m_toolbox/m_settingtoolwid.h \
    $$PWD/m_toolbox/m_simulationtoolwid.h \
    $$PWD/m_sql/m_dbalarm.h \
    $$PWD/m_sql/m_dbenv.h \
    $$PWD/m_sql/m_dbmodbuscmd.h \
    $$PWD/m_sql/m_dbmodbustrans.h \
    $$PWD/m_sql/m_dblinerecords.h \
    $$PWD/m_sql/m_dblinethresholds.h \
    $$PWD/m_sql/m_dboutputrecords.h \
    $$PWD/m_dp/m_dpsavelinethreshold.h \
    $$PWD/m_dp/m_dpsaveoutput.h \
    $$PWD/m_dp/m_dpthread.h \
    $$PWD/m_logs/m_logalarmwid.h \
    $$PWD/m_logs/m_logenvwid.h \
    $$PWD/m_logs/m_logmodbuscmdwid.h \
    $$PWD/m_logs/m_logmodbustranswid.h \
    $$PWD/m_logs/m_loglinerecordwid.h \
    $$PWD/m_logs/m_loglinethresholdwid.h \
    $$PWD/m_logs/m_logoutputrecordwid.h \
    $$PWD/m_logs/m_logswid.h \
    $$PWD/m_simulate/m_simulatewid.h \
    $$PWD/m_simulate/m_simulatethread.h \
    $$PWD/m_test/m_testrtu/mtest_rtuthread.h \
    $$PWD/m_test/m_testsw/mtest_switemwid.h \
    $$PWD/m_test/m_testsw/mtest_swwid.h \
    $$PWD/m_test/m_testthreshold/mtest_thresholditemwid.h \
    $$PWD/m_test/m_testthreshold/mtest_thresholdoutputwid.h \
    $$PWD/m_test/m_testline/mtest_lineitemwid.h \
    $$PWD/m_test/m_testline/mtest_lineunitwid.h \
    $$PWD/m_test/m_testline/mtest_linewid.h \
    $$PWD/m_test/m_testele/mtest_eleitemwid.h \
    $$PWD/m_test/m_testele/mtest_outputelewid.h \
    $$PWD/m_test/m_testenv/mtest_envitemwid.h \
    $$PWD/m_test/m_testenv/mtest_envunitwid.h \
    $$PWD/m_test/m_testenv/mtest_envwid.h \
    $$PWD/m_test/mtest_mainwid.h \
    $$PWD/m_service/json/m_buildjson.h \
    $$PWD/m_service/m_servicethread.h \
    $$PWD/m_dp/m_dpalarmsave.h \
    $$PWD/m_dp/m_dpsaveenv.h \
    $$PWD/m_dp/m_dpsavelinerecord.h \
    $$PWD/m_dp/m_dpsavetrans.h

	
SOURCES += \
    $$PWD/mpdu_mainwid.cpp \
    $$PWD/m_toolbox/mpdu_toolboxwid.cpp \
    $$PWD/m_rtu/m_rturecv.cpp \
    $$PWD/m_rtu/m_rtusent.cpp \
    $$PWD/m_rtu/m_rtutrans.cpp \
    $$PWD/m_com/m_datapackets.cpp \
    $$PWD/m_com/m_configfile.cpp \
    $$PWD/m_toolbox/m_logstoolwid.cpp \
    $$PWD/m_toolbox/m_settingtoolwid.cpp \
    $$PWD/m_toolbox/m_simulationtoolwid.cpp \
    $$PWD/m_sql/m_dbalarm.cpp \
    $$PWD/m_sql/m_dbenv.cpp \
    $$PWD/m_sql/m_dbmodbuscmd.cpp \
    $$PWD/m_sql/m_dbmodbustrans.cpp \
    $$PWD/m_sql/m_dblinerecords.cpp \
    $$PWD/m_sql/m_dblinethresholds.cpp \
    $$PWD/m_sql/m_dboutputrecords.cpp \
    $$PWD/m_dp/m_dpsavelinethreshold.cpp \
    $$PWD/m_dp/m_dpsaveoutput.cpp \
    $$PWD/m_dp/m_dpthread.cpp \
    $$PWD/m_logs/m_logalarmwid.cpp \
    $$PWD/m_logs/m_logenvwid.cpp \
    $$PWD/m_logs/m_logmodbuscmdwid.cpp \
    $$PWD/m_logs/m_logmodbustranswid.cpp \
    $$PWD/m_logs/m_loglinerecordwid.cpp \
    $$PWD/m_logs/m_loglinethresholdwid.cpp \
    $$PWD/m_logs/m_logoutputrecordwid.cpp \
    $$PWD/m_logs/m_logswid.cpp \
    $$PWD/m_simulate/m_simulatewid.cpp \
    $$PWD/m_simulate/m_simulatethread.cpp \
    $$PWD/m_test/m_testrtu/mtest_rtuthread.cpp \
    $$PWD/m_test/m_testsw/mtest_switemwid.cpp \
    $$PWD/m_test/m_testsw/mtest_swwid.cpp \
    $$PWD/m_test/m_testthreshold/mtest_thresholditemwid.cpp \
    $$PWD/m_test/m_testthreshold/mtest_thresholdoutputwid.cpp \
    $$PWD/m_test/m_testline/mtest_lineitemwid.cpp \
    $$PWD/m_test/m_testline/mtest_lineunitwid.cpp \
    $$PWD/m_test/m_testline/mtest_linewid.cpp \
    $$PWD/m_test/m_testele/mtest_eleitemwid.cpp \
    $$PWD/m_test/m_testele/mtest_outputelewid.cpp \
    $$PWD/m_test/m_testenv/mtest_envitemwid.cpp \
    $$PWD/m_test/m_testenv/mtest_envunitwid.cpp \
    $$PWD/m_test/m_testenv/mtest_envwid.cpp \
    $$PWD/m_test/mtest_mainwid.cpp \
    $$PWD/m_service/json/m_buildjson.cpp \
    $$PWD/m_service/m_servicethread.cpp \
    $$PWD/m_dp/m_dpalarmsave.cpp \
    $$PWD/m_dp/m_dpsaveenv.cpp \
    $$PWD/m_dp/m_dpsavelinerecord.cpp \
    $$PWD/m_dp/m_dpsavetrans.cpp

FORMS += \
    $$PWD/mpdu_mainwid.ui \
    $$PWD/m_toolbox/mpdu_toolboxwid.ui \
    $$PWD/m_toolbox/m_logstoolwid.ui \
    $$PWD/m_toolbox/m_settingtoolwid.ui \
    $$PWD/m_toolbox/m_simulationtoolwid.ui \
    $$PWD/m_logs/m_logswid.ui \
    $$PWD/m_simulate/m_simulatewid.ui \
    $$PWD/m_test/m_testsw/mtest_switemwid.ui \
    $$PWD/m_test/m_testsw/mtest_swwid.ui \
    $$PWD/m_test/m_testthreshold/mtest_thresholditemwid.ui \
    $$PWD/m_test/m_testthreshold/mtest_thresholdoutputwid.ui \
    $$PWD/m_test/m_testline/mtest_lineitemwid.ui \
    $$PWD/m_test/m_testline/mtest_lineunitwid.ui \
    $$PWD/m_test/m_testline/mtest_linewid.ui \
    $$PWD/m_test/m_testele/mtest_eleitemwid.ui \
    $$PWD/m_test/m_testele/mtest_outputelewid.ui \
    $$PWD/m_test/m_testenv/mtest_envitemwid.ui \
    $$PWD/m_test/m_testenv/mtest_envunitwid.ui \
    $$PWD/m_test/m_testenv/mtest_envwid.ui \
    $$PWD/m_test/mtest_mainwid.ui





