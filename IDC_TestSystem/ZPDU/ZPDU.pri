
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
    $$PWD/zpdu_mainwid.h

	
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
    $$PWD/zpdu_mainwid.cpp

FORMS += \
    $$PWD/z_logs/z_logswid.ui \
    $$PWD/z_simulate/z_simulatewid.ui \
    $$PWD/z_toolbox/z_simulationtoolwid.ui \
    $$PWD/z_toolbox/z_settingtoolwid.ui \
    $$PWD/z_toolbox/z_logstoolwid.ui \
    $$PWD/z_toolbox/z_toolboxwid.ui \
    $$PWD/zpdu_mainwid.ui





