
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/ip_rtu/ip_rtusent.h \
    $$PWD/ip_rtu/ip_rturecv.h \
    $$PWD/ip_com/ipdatapackets.h \
    $$PWD/ip_rtu/ip_rtutrans.h \
    $$PWD/ip_mainwid.h \
    $$PWD/ip_com/ipconfigfile.h \
    $$PWD/ip_toolbox/ip_toolboxwid.h \
    $$PWD/ip_toolbox/ip_settingtoolwid.h \
    $$PWD/ip_toolbox/ip_logstoolwid.h \
    $$PWD/ip_sql/ipdbthresholds.h \
    $$PWD/ip_sql/ipdbrealrecords.h \
    $$PWD/ip_sql/ipdbmodbustrans.h \
    $$PWD/ip_sql/ipdbmodbuscmd.h \
    $$PWD/ip_sql/ipdbenv.h \
    $$PWD/ip_sql/ipdbalarm.h \
    $$PWD/ip_logs/iplogalarmwid.h \
    $$PWD/ip_logs/iplogenvwid.h \
    $$PWD/ip_logs/iplogmodbuscmdwid.h \
    $$PWD/ip_logs/iplogmodbustranswid.h \
    $$PWD/ip_logs/iplogrealrecordwid.h \
    $$PWD/ip_logs/iplogthresholdwid.h \
    $$PWD/ip_logs/iplogswid.h \
    $$PWD/ip_dp/ip_dpsavethreshold.h \
    $$PWD/ip_dp/ip_dpsaveenv.h \
    $$PWD/ip_dp/ip_dpthread.h \
    $$PWD/ip_service/ip_servicethread.h \
    $$PWD/ip_service/json/ip_buildjson.h \
    $$PWD/ip_dp/ip_dpalarmsave.h \
    $$PWD/ip_dp/ip_dpsaverecord.h \
    $$PWD/ip_dp/ip_dpsavetrans.h \
    $$PWD/ip_toolbox/ip_modetoolwid.h \
    $$PWD/ip_toolbox/ip_statustoolwid.h \
    $$PWD/ip_rtu/ip_rtuthread.h \
    $$PWD/ip_status/ip_statuswid.h \
    $$PWD/ip_snmp/ip_snmpsend.h \
    $$PWD/ip_snmp/ip_snmprecv.h \
    $$PWD/ip_snmp/ip_snmptrans.h

	
SOURCES += \
    $$PWD/ip_rtu/ip_rtusent.cpp \
    $$PWD/ip_rtu/ip_rturecv.cpp \
    $$PWD/ip_com/ipdatapackets.cpp \
    $$PWD/ip_rtu/ip_rtutrans.cpp \
    $$PWD/ip_mainwid.cpp \
    $$PWD/ip_com/ipconfigfile.cpp \
    $$PWD/ip_toolbox/ip_toolboxwid.cpp \
    $$PWD/ip_toolbox/ip_settingtoolwid.cpp \
    $$PWD/ip_toolbox/ip_logstoolwid.cpp \
    $$PWD/ip_sql/ipdbthresholds.cpp \
    $$PWD/ip_sql/ipdbrealrecords.cpp \
    $$PWD/ip_sql/ipdbmodbustrans.cpp \
    $$PWD/ip_sql/ipdbmodbuscmd.cpp \
    $$PWD/ip_sql/ipdbenv.cpp \
    $$PWD/ip_sql/ipdbalarm.cpp \
    $$PWD/ip_logs/iplogalarmwid.cpp \
    $$PWD/ip_logs/iplogenvwid.cpp \
    $$PWD/ip_logs/iplogmodbuscmdwid.cpp \
    $$PWD/ip_logs/iplogmodbustranswid.cpp \
    $$PWD/ip_logs/iplogrealrecordwid.cpp \
    $$PWD/ip_logs/iplogthresholdwid.cpp \
    $$PWD/ip_logs/iplogswid.cpp \
    $$PWD/ip_dp/ip_dpsavethreshold.cpp \
    $$PWD/ip_dp/ip_dpthread.cpp \
    $$PWD/ip_service/ip_servicethread.cpp \
    $$PWD/ip_service/json/ip_buildjson.cpp \
    $$PWD/ip_dp/ip_dpalarmsave.cpp \
    $$PWD/ip_dp/ip_dpsaveenv.cpp \
    $$PWD/ip_dp/ip_dpsaverecord.cpp \
    $$PWD/ip_dp/ip_dpsavetrans.cpp \
    $$PWD/ip_toolbox/ip_modetoolwid.cpp \
    $$PWD/ip_toolbox/ip_statustoolwid.cpp \
    $$PWD/ip_rtu/ip_rtuthread.cpp \
    $$PWD/ip_status/ip_statuswid.cpp \
    $$PWD/ip_snmp/ip_snmpsend.cpp \
    $$PWD/ip_snmp/ip_snmprecv.cpp \
    $$PWD/ip_snmp/ip_snmptrans.cpp

FORMS += \
    $$PWD/ip_mainwid.ui \
    $$PWD/ip_toolbox/ip_toolboxwid.ui \
    $$PWD/ip_logs/iplogswid.ui \
    $$PWD/ip_status/ip_statuswid.ui





