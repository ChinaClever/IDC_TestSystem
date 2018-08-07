
INCLUDEPATH += $$PWD

include(mpdu_test/mpdu_test.pri)

HEADERS += \
    $$PWD/mpdu_mainwid.h \
    $$PWD/mpdu_toolbox/mpdu_toolboxwid.h \
    $$PWD/m_rtu/m_rturecv.h \
    $$PWD/m_rtu/m_rtusent.h \
    $$PWD/m_rtu/m_rturegenum.h \
    $$PWD/m_rtu/m_rtutrans.h \
    $$PWD/m_com/m_datapackets.h \
    $$PWD/m_com/m_configfile.h \
    $$PWD/mpdu_toolbox/m_logstoolwid.h \
    $$PWD/mpdu_toolbox/m_settingtoolwid.h \
    $$PWD/mpdu_toolbox/m_simulationtoolwid.h \
    $$PWD/m_sql/m_dbalarm.h \
    $$PWD/m_sql/m_dbenv.h \
    $$PWD/m_sql/m_dbmodbuscmd.h \
    $$PWD/m_sql/m_dbmodbustrans.h \
    $$PWD/m_sql/m_dblinerecords.h \
    $$PWD/m_sql/m_dblinethresholds.h \
    $$PWD/m_sql/m_dboutputrecords.h \
    $$PWD/m_dp/m_dpalarmslave.h \
    $$PWD/m_dp/m_dpsavelinethreshold.h \
    $$PWD/m_dp/m_dpslaveenv.h \
    $$PWD/m_dp/m_dpslavelinerecord.h \
    $$PWD/m_dp/m_dpslavetrans.h \
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
    $$PWD/m_simulate/m_simulatethread.h

	
SOURCES += \
    $$PWD/mpdu_mainwid.cpp \
    $$PWD/mpdu_toolbox/mpdu_toolboxwid.cpp \
    $$PWD/m_rtu/m_rturecv.cpp \
    $$PWD/m_rtu/m_rtusent.cpp \
    $$PWD/m_rtu/m_rtutrans.cpp \
    $$PWD/m_com/m_datapackets.cpp \
    $$PWD/m_com/m_configfile.cpp \
    $$PWD/mpdu_toolbox/m_logstoolwid.cpp \
    $$PWD/mpdu_toolbox/m_settingtoolwid.cpp \
    $$PWD/mpdu_toolbox/m_simulationtoolwid.cpp \
    $$PWD/m_sql/m_dbalarm.cpp \
    $$PWD/m_sql/m_dbenv.cpp \
    $$PWD/m_sql/m_dbmodbuscmd.cpp \
    $$PWD/m_sql/m_dbmodbustrans.cpp \
    $$PWD/m_sql/m_dblinerecords.cpp \
    $$PWD/m_sql/m_dblinethresholds.cpp \
    $$PWD/m_sql/m_dboutputrecords.cpp \
    $$PWD/m_dp/m_dpalarmslave.cpp \
    $$PWD/m_dp/m_dpsavelinethreshold.cpp \
    $$PWD/m_dp/m_dpslaveenv.cpp \
    $$PWD/m_dp/m_dpslavelinerecord.cpp \
    $$PWD/m_dp/m_dpslavetrans.cpp \
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
    $$PWD/m_simulate/m_simulatethread.cpp

FORMS += \
    $$PWD/mpdu_mainwid.ui \
    $$PWD/mpdu_toolbox/mpdu_toolboxwid.ui \
    $$PWD/mpdu_toolbox/m_logstoolwid.ui \
    $$PWD/mpdu_toolbox/m_settingtoolwid.ui \
    $$PWD/mpdu_toolbox/m_simulationtoolwid.ui \
    $$PWD/m_logs/m_logswid.ui \
    $$PWD/m_simulate/m_simulatewid.ui





